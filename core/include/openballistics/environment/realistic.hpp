#ifndef OPENBALLISTICS_ENVIRONMENT_REALISTIC_HPP
#define OPENBALLISTICS_ENVIRONMENT_REALISTIC_HPP

#include "../types.hpp"
#include "../interpolator/lazy_linear.hpp"
#include "../interpolator/lazy_trilinear.hpp"
#include <cstdint>
#include <functional>
#include <utility>
#include <optional>

namespace openballistics::environment
{
    class realistic
    {
    public:
        [[nodiscard]] static realistic isa()
        {
            static constexpr scalar standard_gravity = 9.80665;
            static constexpr scalar universal_gas_constant = 8'314.32;
            static constexpr scalar mean_molar_mass = 28.96442;
            static constexpr scalar earth_radius = 6'356'766.0;
            static constexpr scalar R = universal_gas_constant / mean_molar_mass;

            struct layer
            {
                scalar base_geopotential_altitude;
                scalar base_temperature;
                scalar lapse_rate;
                scalar base_pressure;
            };

            static constexpr layer layers[] = {
                {0.0, 288.15, -0.0065, 101325.000000000000000},
                {11000.0, 216.65, +0.0000, 22632.040548385379225},
                {20000.0, 216.65, +0.0010, 5474.877637796043928},
                {32000.0, 228.65, +0.0028, 868.015831836590792},
                {47000.0, 270.65, +0.0000, 110.905783471879701},
                {51000.0, 270.65, -0.0028, 66.938534671596116},
                {71000.0, 214.65, -0.0020, 3.956392697109635},
            };

            static constexpr auto to_geopotential = [](const scalar z) -> scalar
            {
                return earth_radius * z / (earth_radius + z);
            };

            static constexpr auto find_layer = [](const scalar h) -> const layer &
            {
                uint8_t i = static_cast<uint8_t>(std::size(layers)) - 1;
                while (i > 0 && h < layers[i].base_geopotential_altitude)
                    --i;
                return layers[i];
            };

            static constexpr auto temperature_profile = [](const scalar z) -> scalar
            {
                const scalar h = to_geopotential(z);
                const layer &l = find_layer(h);
                return l.base_temperature + l.lapse_rate * (h - l.base_geopotential_altitude);
            };

            static constexpr auto pressure_profile = [](const scalar z) -> scalar
            {
                const scalar h = to_geopotential(z);
                const layer &l = find_layer(h);
                const scalar dh = h - l.base_geopotential_altitude;
                if (l.lapse_rate != 0.0)
                    return l.base_pressure *
                           std::pow(1.0 + l.lapse_rate * dh / l.base_temperature,
                                    -standard_gravity / (l.lapse_rate * R));
                return l.base_pressure *
                       std::exp(-standard_gravity * dh / (R * l.base_temperature));
            };

            return realistic{}
                .set_adiabatic_index(1.4)
                .set_specific_gas_constant(R)
                .set_temperature(+temperature_profile)
                .set_pressure(+pressure_profile)
                .set_gravity(vector3(0.0, 0.0, -standard_gravity))
                .set_wind_velocity(vector3(0.0, 0.0, 0.0));
        }

    public:
#pragma region "CODEGEN ENV-R-SET" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		realistic &set_adiabatic_index(const scalar value)
		{
			m_adiabatic_index_constant = value;
			m_adiabatic_index_source = 1;
			return *this;
		}

		realistic &set_specific_gas_constant(const scalar value)
		{
			m_specific_gas_constant_constant = value;
			m_specific_gas_constant_source = 1;
			return *this;
		}

		realistic &set_temperature(scalar value)
		{
			m_temperature_constant = std::move(value);
			m_temperature_source = 1;
			return *this;
		}
		realistic &set_temperature(scalar (*profile)(scalar))
		{
			m_temperature_profile = profile;
			m_temperature_source = 2;
			return *this;
		}
		realistic &set_temperature(scalar (*field)(const vector3 &))
		{
			m_temperature_field = field;
			m_temperature_source = 3;
			return *this;
		}
		realistic &set_temperature(std::function<scalar(scalar)> profile)
		{
			m_temperature_profile_virtual = std::move(profile);
			m_temperature_source = 4;
			return *this;
		}
		realistic &set_temperature(std::function<scalar(vector3)> field)
		{
			m_temperature_field_property_virtual = std::move(field);
			m_temperature_source = 5;
			return *this;
		}
		realistic &set_temperature(std::function<scalar(scalar)> profile, const scalar interpolator_step)
		{
			m_temperature_profile_interpolator = interpolator::lazy_linear<scalar>(std::move(profile), interpolator_step);
			m_temperature_source = 6;
			return *this;
		}
		realistic &set_temperature(std::function<scalar(vector3)> field, const scalar interpolator_step)
		{
			m_temperature_field_property_interpolator = interpolator::lazy_trilinear<scalar>(std::move(field), interpolator_step);
			m_temperature_source = 7;
			return *this;
		}

		realistic &set_pressure(scalar value)
		{
			m_pressure_constant = std::move(value);
			m_pressure_source = 1;
			return *this;
		}
		realistic &set_pressure(scalar (*profile)(scalar))
		{
			m_pressure_profile = profile;
			m_pressure_source = 2;
			return *this;
		}
		realistic &set_pressure(scalar (*field)(const vector3 &))
		{
			m_pressure_field = field;
			m_pressure_source = 3;
			return *this;
		}
		realistic &set_pressure(std::function<scalar(scalar)> profile)
		{
			m_pressure_profile_virtual = std::move(profile);
			m_pressure_source = 4;
			return *this;
		}
		realistic &set_pressure(std::function<scalar(vector3)> field)
		{
			m_pressure_field_property_virtual = std::move(field);
			m_pressure_source = 5;
			return *this;
		}
		realistic &set_pressure(std::function<scalar(scalar)> profile, const scalar interpolator_step)
		{
			m_pressure_profile_interpolator = interpolator::lazy_linear<scalar>(std::move(profile), interpolator_step);
			m_pressure_source = 6;
			return *this;
		}
		realistic &set_pressure(std::function<scalar(vector3)> field, const scalar interpolator_step)
		{
			m_pressure_field_property_interpolator = interpolator::lazy_trilinear<scalar>(std::move(field), interpolator_step);
			m_pressure_source = 7;
			return *this;
		}

		realistic &set_gravity(vector3 value)
		{
			m_gravity_constant = std::move(value);
			m_gravity_source = 1;
			return *this;
		}
		realistic &set_gravity(vector3 (*profile)(scalar))
		{
			m_gravity_profile = profile;
			m_gravity_source = 2;
			return *this;
		}
		realistic &set_gravity(vector3 (*field)(const vector3 &))
		{
			m_gravity_field = field;
			m_gravity_source = 3;
			return *this;
		}
		realistic &set_gravity(std::function<vector3(scalar)> profile)
		{
			m_gravity_profile_virtual = std::move(profile);
			m_gravity_source = 4;
			return *this;
		}
		realistic &set_gravity(std::function<vector3(vector3)> field)
		{
			m_gravity_field_property_virtual = std::move(field);
			m_gravity_source = 5;
			return *this;
		}
		realistic &set_gravity(std::function<vector3(scalar)> profile, const scalar interpolator_step)
		{
			m_gravity_profile_interpolator = interpolator::lazy_linear<vector3>(std::move(profile), interpolator_step);
			m_gravity_source = 6;
			return *this;
		}
		realistic &set_gravity(std::function<vector3(vector3)> field, const scalar interpolator_step)
		{
			m_gravity_field_property_interpolator = interpolator::lazy_trilinear<vector3>(std::move(field), interpolator_step);
			m_gravity_source = 7;
			return *this;
		}

		realistic &set_wind_velocity(vector3 value)
		{
			m_wind_velocity_constant = std::move(value);
			m_wind_velocity_source = 1;
			return *this;
		}
		realistic &set_wind_velocity(vector3 (*profile)(scalar))
		{
			m_wind_velocity_profile = profile;
			m_wind_velocity_source = 2;
			return *this;
		}
		realistic &set_wind_velocity(vector3 (*field)(const vector3 &))
		{
			m_wind_velocity_field = field;
			m_wind_velocity_source = 3;
			return *this;
		}
		realistic &set_wind_velocity(std::function<vector3(scalar)> profile)
		{
			m_wind_velocity_profile_virtual = std::move(profile);
			m_wind_velocity_source = 4;
			return *this;
		}
		realistic &set_wind_velocity(std::function<vector3(vector3)> field)
		{
			m_wind_velocity_field_property_virtual = std::move(field);
			m_wind_velocity_source = 5;
			return *this;
		}
		realistic &set_wind_velocity(std::function<vector3(scalar)> profile, const scalar interpolator_step)
		{
			m_wind_velocity_profile_interpolator = interpolator::lazy_linear<vector3>(std::move(profile), interpolator_step);
			m_wind_velocity_source = 6;
			return *this;
		}
		realistic &set_wind_velocity(std::function<vector3(vector3)> field, const scalar interpolator_step)
		{
			m_wind_velocity_field_property_interpolator = interpolator::lazy_trilinear<vector3>(std::move(field), interpolator_step);
			m_wind_velocity_source = 7;
			return *this;
		}
#pragma endregion "CODEGEN ENV-R-SET"

#pragma region "CODEGEN ENV-R-GET" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		[[nodiscard]] scalar adiabatic_index() const
		{
			if (m_adiabatic_index_source == 1) return m_adiabatic_index_constant;
			throw std::bad_optional_access{};
		}

		[[nodiscard]] scalar specific_gas_constant() const
		{
			if (m_specific_gas_constant_source == 1) return m_specific_gas_constant_constant;
			throw std::bad_optional_access{};
		}

		[[nodiscard]] scalar temperature(const vector3 &position) const
		{
			switch (m_temperature_source)
			{
			case 1: return m_temperature_constant;
			case 2: return m_temperature_profile(position.z());
			case 3: return m_temperature_field(position);
			case 4: return m_temperature_profile_virtual(position.z());
			case 5: return m_temperature_field_property_virtual(position);
			case 6: return m_temperature_profile_interpolator.evaluate(position.z());
			case 7: return m_temperature_field_property_interpolator.evaluate(position);
			default: throw std::bad_optional_access{};
			}
		}

		[[nodiscard]] scalar pressure(const vector3 &position) const
		{
			switch (m_pressure_source)
			{
			case 1: return m_pressure_constant;
			case 2: return m_pressure_profile(position.z());
			case 3: return m_pressure_field(position);
			case 4: return m_pressure_profile_virtual(position.z());
			case 5: return m_pressure_field_property_virtual(position);
			case 6: return m_pressure_profile_interpolator.evaluate(position.z());
			case 7: return m_pressure_field_property_interpolator.evaluate(position);
			default: throw std::bad_optional_access{};
			}
		}

		[[nodiscard]] vector3 gravity(const vector3 &position) const
		{
			switch (m_gravity_source)
			{
			case 1: return m_gravity_constant;
			case 2: return m_gravity_profile(position.z());
			case 3: return m_gravity_field(position);
			case 4: return m_gravity_profile_virtual(position.z());
			case 5: return m_gravity_field_property_virtual(position);
			case 6: return m_gravity_profile_interpolator.evaluate(position.z());
			case 7: return m_gravity_field_property_interpolator.evaluate(position);
			default: throw std::bad_optional_access{};
			}
		}

		[[nodiscard]] vector3 wind_velocity(const vector3 &position) const
		{
			switch (m_wind_velocity_source)
			{
			case 1: return m_wind_velocity_constant;
			case 2: return m_wind_velocity_profile(position.z());
			case 3: return m_wind_velocity_field(position);
			case 4: return m_wind_velocity_profile_virtual(position.z());
			case 5: return m_wind_velocity_field_property_virtual(position);
			case 6: return m_wind_velocity_profile_interpolator.evaluate(position.z());
			case 7: return m_wind_velocity_field_property_interpolator.evaluate(position);
			default: throw std::bad_optional_access{};
			}
		}
#pragma endregion "CODEGEN ENV-R-GET"

    private:
#pragma region "CODEGEN ENV-R-MEM" // AUTO-GENERATED - DO NOT EDIT MANUALLY
		bool m_adiabatic_index_source = 0;
		scalar m_adiabatic_index_constant;

		bool m_specific_gas_constant_source = 0;
		scalar m_specific_gas_constant_constant;

		uint8_t m_temperature_source = 0;
		scalar m_temperature_constant;
		scalar (*m_temperature_profile)(scalar);
		scalar (*m_temperature_field)(const vector3 &);
		std::function<scalar(scalar)> m_temperature_profile_virtual;
		std::function<scalar(vector3)> m_temperature_field_property_virtual;
		interpolator::lazy_linear<scalar> m_temperature_profile_interpolator;
		interpolator::lazy_trilinear<scalar> m_temperature_field_property_interpolator;

		uint8_t m_pressure_source = 0;
		scalar m_pressure_constant;
		scalar (*m_pressure_profile)(scalar);
		scalar (*m_pressure_field)(const vector3 &);
		std::function<scalar(scalar)> m_pressure_profile_virtual;
		std::function<scalar(vector3)> m_pressure_field_property_virtual;
		interpolator::lazy_linear<scalar> m_pressure_profile_interpolator;
		interpolator::lazy_trilinear<scalar> m_pressure_field_property_interpolator;

		uint8_t m_gravity_source = 0;
		vector3 m_gravity_constant;
		vector3 (*m_gravity_profile)(scalar);
		vector3 (*m_gravity_field)(const vector3 &);
		std::function<vector3(scalar)> m_gravity_profile_virtual;
		std::function<vector3(vector3)> m_gravity_field_property_virtual;
		interpolator::lazy_linear<vector3> m_gravity_profile_interpolator;
		interpolator::lazy_trilinear<vector3> m_gravity_field_property_interpolator;

		uint8_t m_wind_velocity_source = 0;
		vector3 m_wind_velocity_constant;
		vector3 (*m_wind_velocity_profile)(scalar);
		vector3 (*m_wind_velocity_field)(const vector3 &);
		std::function<vector3(scalar)> m_wind_velocity_profile_virtual;
		std::function<vector3(vector3)> m_wind_velocity_field_property_virtual;
		interpolator::lazy_linear<vector3> m_wind_velocity_profile_interpolator;
		interpolator::lazy_trilinear<vector3> m_wind_velocity_field_property_interpolator;
#pragma endregion "CODEGEN ENV-R-MEM"
    };
}

#endif // OPENBALLISTICS_ENVIRONMENT_REALISTIC_HPP