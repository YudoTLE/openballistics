#ifndef OPENBALLISTICS_MODEL_MODIFIED_POINT_MASS_HPP
#define OPENBALLISTICS_MODEL_MODIFIED_POINT_MASS_HPP

#include "../types.hpp"
#include "../numbers.hpp"
#include <Eigen/Dense>
#include <cmath>

namespace openballistics::model
{
    template <typename Derived>
    class modified_point_mass
    {
    public:
        using state = Eigen::Matrix<scalar, 7, 1>;
        struct weapon_parameters
        {
#pragma region "CODEGEN MODEL-MPM-DEF" // AUTO-GENERATED - DO NOT EDIT MANUALLY
			scalar muzzle_velocity;
			scalar rifling_twist;
#pragma endregion "CODEGEN MODEL-MPM-DEF"
        };

    protected:
        void initialize(
            state &x,
            const vector3 &launch_position,
            const vector3 &launch_direction,
            const vector3 &platform_velocity,
            const weapon_parameters &parameters) const
        {
            x << launch_position,
                platform_velocity + launch_direction * parameters.muzzle_velocity,
                2.0 * numbers::pi<scalar> * parameters.muzzle_velocity / parameters.rifling_twist;
        }

        void derivative(
            const state &x,
            state &dxdt,
            const scalar t) const
        {
            constexpr scalar epsilon_v = 1e-6;
            constexpr scalar epsilon_cma = 1e-6;

            const vector3 r = x.head<3>();
            const vector3 v = x.segment<3>(3);
            const scalar p = x(6);

            const auto &environment = static_cast<const Derived *>(this)->environment;
            const auto &projectile = static_cast<const Derived *>(this)->projectile;

            const vector3 V_rel = v - environment.wind_velocity(r);
            const scalar V2 = V_rel.squaredNorm();
            const scalar V = std::sqrt(V2);

            const vector3 g = environment.gravity(r);
            const scalar T = environment.temperature(r);
            const scalar P = environment.pressure(r);
            const scalar R = environment.specific_gas_constant();
            const scalar rho = P / (R * T);
            const scalar a_s = std::sqrt(environment.adiabatic_index() * R * T);
            const scalar mach = V / a_s;

            const scalar m = projectile.mass();
            const scalar d = projectile.diameter();
            const scalar S = projectile.reference_area();
            const scalar Ix = projectile.axial_moment_of_inertia();

            const scalar C_D = projectile.drag_force_coefficient(mach);
            const scalar C_spin = projectile.spin_damping_moment_coefficient(mach);

            const scalar K_drag = (0.5 * rho * V * S * C_D) / m;

            scalar W_g = 1.0;
            scalar W_v = -K_drag;
            scalar W_c = 0.0;

            if (V >= epsilon_v)
            {
                const scalar C_Ma = projectile.overturning_moment_coefficient(mach);

                if (std::abs(C_Ma) >= epsilon_cma)
                {
                    const scalar C_La = projectile.lift_force_coefficient(mach);
                    const scalar C_mag_f = projectile.magnus_force_coefficient(mach);

                    const scalar Ix_p = Ix * p;
                    const scalar denom = m * V2 * C_Ma;

                    const scalar K_lift = (Ix_p * C_La) / (denom * d);
                    const scalar K_magnus = (Ix_p * p * C_mag_f) / denom;

                    W_g += K_magnus;
                    W_v -= K_magnus * (V_rel.dot(g) / V2);
                    W_c = -K_lift;
                }
            }

            dxdt.head<3>() = v;
            dxdt.segment<3>(3) = (W_g * g) + (W_v * V_rel) + (W_c * V_rel.cross(g));
            dxdt(6) = (0.5 * rho * V * S * d * d * p * C_spin) / Ix;
        }
    };
}

#endif // OPENBALLISTICS_MODEL_MODIFIED_POINT_MASS_HPP