#ifndef OPENBALLISTICS_MODEL_POINT_MASS_HPP
#define OPENBALLISTICS_MODEL_POINT_MASS_HPP

#include "../types.hpp"
#include <Eigen/Dense>

namespace openballistics::model
{
    template <typename Derived>
    class point_mass
    {
    public:
        using state = Eigen::Matrix<scalar, 6, 1>;
        struct weapon_parameters
        {
#pragma region "CODEGEN MODEL-PM-DEF" // AUTO-GENERATED - DO NOT EDIT MANUALLY
			scalar muzzle_velocity;
#pragma endregion "CODEGEN MODEL-PM-DEF"
        };

    protected:
        void initialize(
            state &x,
            const vector3 &launch_position,
            const vector3 &launch_direction,
            const vector3 &platform_velocity,
            const weapon_parameters &parameters) const
        {
            x << launch_position, platform_velocity + launch_direction * parameters.muzzle_velocity;
        }

        void derivative(
            const state &x,
            state &dxdt,
            const scalar t) const
        {
            const vector3 r = x.head<3>();
            const vector3 v = x.tail<3>();

            const auto &environment = static_cast<const Derived *>(this)->environment;
            const auto &projectile = static_cast<const Derived *>(this)->projectile;

            const vector3 V_rel = v - environment.wind_velocity(r);
            const scalar V = V_rel.norm();

            const vector3 g = environment.gravity(r);
            const scalar T = environment.temperature(r);
            const scalar P = environment.pressure(r);
            const scalar rho = P / (environment.specific_gas_constant() * T);
            const scalar a_s = std::sqrt(
                environment.adiabatic_index() *
                environment.specific_gas_constant() * T);
            const scalar mach = V / a_s;

            const scalar m = projectile.mass();
            const scalar S = projectile.reference_area();
            const scalar C_D = projectile.drag_force_coefficient(mach);

            dxdt.head<3>() = v;
            dxdt.tail<3>() = g - 0.5 * rho * S * C_D / m * V * V_rel;
        }
    };
}

#endif // OPENBALLISTICS_MODEL_POINT_MASS_HPP