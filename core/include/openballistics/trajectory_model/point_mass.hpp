#ifndef OPENBALLISTICS_TRAJECTORY_MODEL_POINT_MASS_HPP
#define OPENBALLISTICS_TRAJECTORY_MODEL_POINT_MASS_HPP

#include "../types.hpp"
#include "../numbers.hpp"
#include <Eigen/Dense>

namespace openballistics::trajectory_model
{
    template <typename Derived>
    class point_mass
    {
    public:
        using state = Eigen::Matrix<scalar, 6, 1>;
        struct weapon_parameters
        {
#pragma region "CODEGEN TM-PM-DEF" // AUTO-GENERATED - DO NOT EDIT MANUALLY
			scalar muzzle_velocity;
#pragma endregion "CODEGEN TM-PM-DEF"
        };

    protected:
        void initialize(
            state &y,
            const vector3 &launch_position,
            const vector3 &launch_direction,
            const vector3 &platform_velocity,
            const weapon_parameters &parameters) const
        {
            y << launch_position, platform_velocity + launch_direction * parameters.muzzle_velocity;
        }

        void derivative(
            const state &y,
            state &dydt,
            const scalar t) const
        {
            const vector3 x_ = y.head<3>();
            const vector3 u_ = y.tail<3>();

            const auto &environment = static_cast<const Derived *>(this)->environment;
            const auto &projectile = static_cast<const Derived *>(this)->projectile;

            const vector3 w_ = environment.wind_velocity(x_);
            const vector3 g_ = environment.gravity(x_);
            const scalar T = environment.temperature(x_);
            const scalar P = environment.pressure(x_);
            const scalar R = environment.specific_gas_constant();
            const scalar k = environment.adiabatic_index();

            const vector3 v_ = u_ - w_;
            const scalar v = v_.norm();

            const scalar rho = P / (R * T);
            const scalar M = v / std::sqrt(k * R * T);

            const scalar m = projectile.mass();
            const scalar d = projectile.diameter();
            
            const scalar i = projectile.form_factor();
            const scalar f_D = projectile.drag_factor();

            const scalar C_D_0 = projectile.drag_force_coefficient(M);

            const scalar C_D_eff = C_D_0 * i * f_D;

            const scalar S = 0.25 * numbers::pi<scalar> * d * d;

            dydt.template head<3>() = u_;
            dydt.template tail<3>() = g_ - 0.5 * rho * S * C_D_eff / m * v * v_;
        }
    };
}

#endif // OPENBALLISTICS_TRAJECTORY_MODEL_POINT_MASS_HPP