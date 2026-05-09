#ifndef OPENBALLISTICS_TRAJECTORY_MODEL_MODIFIED_POINT_MASS_HPP
#define OPENBALLISTICS_TRAJECTORY_MODEL_MODIFIED_POINT_MASS_HPP

#include "../types.hpp"
#include "../numbers.hpp"
#include <Eigen/Dense>
#include <cmath>

namespace openballistics::trajectory_model
{
    template <typename Derived>
    class modified_point_mass
    {
    public:
        using state = Eigen::Matrix<scalar, 7, 1>;
        struct weapon_parameters
        {
#pragma region "CODEGEN TM-MPM-DEF" // AUTO-GENERATED - DO NOT EDIT MANUALLY
			scalar muzzle_velocity;
			scalar twist_of_rifling;
#pragma endregion "CODEGEN TM-MPM-DEF"
        };

    protected:
        void initialize(
            state &y,
            const vector3 &launch_position,
            const vector3 &launch_direction,
            const vector3 &platform_velocity,
            const weapon_parameters &parameters) const
        {
            y << launch_position,
                platform_velocity + launch_direction * parameters.muzzle_velocity,
                2.0 * numbers::pi<scalar> * parameters.muzzle_velocity / parameters.twist_of_rifling;
        }

        void derivative(
            const state &y,
            state &dydt,
            const scalar t) const
        {
            constexpr scalar epsilon_v = 1e-6;
            constexpr scalar epsilon_C_M = 1e-6;
            constexpr scalar tol_a_e = 1e-12;
            constexpr int max_iter_a_e = 5;

            const vector3 x_ = y.template head<3>();
            const vector3 u_ = y.template segment<3>(3);
            const scalar p = y(6);

            const auto &environment = static_cast<const Derived *>(this)->environment;
            const auto &projectile = static_cast<const Derived *>(this)->projectile;

            const vector3 w_ = environment.wind_velocity(x_);
            const vector3 g_ = environment.gravity(x_);
            const scalar T = environment.temperature(x_);
            const scalar P = environment.pressure(x_);
            const scalar R = environment.specific_gas_constant();
            const scalar k = environment.adiabatic_index();

            const vector3 v_ = u_ - w_;
            const scalar v2 = v_.squaredNorm();
            const scalar v = std::sqrt(v2);
            const scalar v4 = v2 * v2;

            const scalar rho = P / (R * T);
            const scalar M = v / std::sqrt(k * R * T);

            const scalar m = projectile.mass();
            const scalar d = projectile.diameter();
            const scalar I_x = projectile.axial_moment_of_inertia();

            const scalar S = 0.25 * numbers::pi<scalar> * d * d;

            const scalar i = projectile.form_factor();
            const scalar f_D = projectile.drag_factor();
            const scalar Q_D = projectile.yaw_drag_factor();

            const scalar C_D_0 = projectile.drag_force_coefficient(M);
            const scalar C_D_a2 = projectile.quadratic_yaw_drag_force_coefficient(M);
            const scalar C_D_a4 = projectile.quartic_yaw_drag_force_coefficient(M);
            const scalar C_spin = projectile.spin_damping_moment_coefficient(M);

            const vector3 GF_ = m * g_;
            vector3 DF_ = vector3::Zero();
            vector3 LF_ = vector3::Zero();
            vector3 MF_ = vector3::Zero();
            vector3 dudt_ = vector3::Zero();

            if (v >= epsilon_v)
            {
                const scalar f_L = projectile.lift_factor();
                const scalar Q_M = projectile.magnus_force_factor();

                const scalar C_L_a = projectile.lift_force_coefficient(M);
                const scalar C_L_a3 = projectile.cubic_lift_force_coefficient(M);
                const scalar C_L_a5 = projectile.quintic_lift_force_coefficient(M);
                const scalar C_magf = projectile.magnus_force_coefficient(M);
                const scalar C_M_a = projectile.overturning_moment_coefficient(M);
                const scalar C_M_a3 = projectile.cubic_overturning_moment_coefficient(M);

                vector3 a_e_ = vector3::Zero();
                scalar a_e = 0.0;

                for (int iter = 0; iter < max_iter_a_e; ++iter)
                {
                    a_e = a_e_.norm();
                    const scalar a2_e = a_e * a_e;
                    const scalar a4_e = a2_e * a2_e;

                    scalar C_M_eff = C_M_a + C_M_a3 * a2_e;
                    if (std::abs(C_M_eff) < epsilon_C_M)
                        break;

                    const scalar Q_D_times_a_e = Q_D * a_e;
                    const scalar Q2_D_times_a2_e = Q_D_times_a_e * Q_D_times_a_e;
                    const scalar Q4_D_times_a4_e = Q2_D_times_a2_e * Q2_D_times_a2_e;

                    const scalar C_D_eff = i * (f_D * C_D_0 + C_D_a2 * Q2_D_times_a2_e + C_D_a4 * Q4_D_times_a4_e);
                    const scalar C_L_eff = f_L * (C_L_a + C_L_a3 * a2_e + C_L_a5 * a4_e);
                    const scalar C_magf_eff = Q_M * C_magf;

                    DF_ = -0.5 * rho * S * C_D_eff * v * v_;
                    LF_ = 0.5 * rho * S * C_L_eff * v2 * a_e_;
                    MF_ = -0.5 * rho * S * d * p * C_magf_eff * a_e_.cross(v_);

                    dudt_ = (GF_ + DF_ + LF_ + MF_) / m;

                    vector3 a_e_new_ = (-2.0 * I_x * p * v_.cross(dudt_)) / (rho * S * d * C_M_eff * v4);
                    if ((a_e_new_ - a_e_).norm() < tol_a_e)
                    {
                        a_e_ = a_e_new_;
                        break;
                    }
                    a_e_ = a_e_new_;
                }
            }
            else
            {
                dudt_ = GF_ / m;
            }

            dydt.template head<3>() = u_;
            dydt.template segment<3>(3) = dudt_;
            dydt(6) = (0.5 * rho * v * S * d * d * p * C_spin) / I_x;
        }
    };
}

#endif // OPENBALLISTICS_TRAJECTORY_MODEL_MODIFIED_POINT_MASS_HPP