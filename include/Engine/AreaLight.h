#ifndef _ENGINE_LIGHT_AREA_LIGHT_H_
#define _ENGINE_LIGHT_AREA_LIGHT_H_

#include <Engine/Light.h>
#include <Basic/UniformGridSampler2D.h>

namespace CppUtil {
	namespace Engine {
		// ����
		class AreaLight : public Light {
		public:
			AreaLight(const RGBf &color = RGBf(1), float intensity = 1, float width = 1, float height = 1)
				: color(color), intensity(intensity), width(width), height(height) { }

		public:
			static const Basic::Ptr<AreaLight> New(const RGBf &color = RGBf(1), float intensity = 1, float width = 1, float height = 1) {
				return Basic::New<AreaLight>(color, intensity, width, height);
			}

		public:
			float Area() const { return width * height; }
			const RGBf LuminancePower() const { return intensity * color; }
			const RGBf Luminance() const { return LuminancePower() / (Area() * Basic::Math::PI); }

		public:
			// ���� L ����
			// !!! p��wi ���ڹ�Դ������ռ���
			// @arg0  in���� p �������� distToLight �� PD
			// @arg1 out��wi ָ���Դ��Ϊ��λ����
			// @arg2 out��p �㵽��Դ������ľ���
			// @arg3 out�������ܶ� probability density
			virtual const RGBf Sample_L(const Point3 & p, Normalf & wi, float & distToLight, float & PD) const override;

			// �����ܶȺ���
			// !!! p��wi ���ڵƵ�����ռ���
			virtual float PDF(const Point3 & p, const Normalf & wi) const override;

			virtual bool IsDelta() const override { return false; }

		public:
			RGBf color;
			float intensity;
			float width;
			float height;

		private:
			// dirToLight ������ ��λ����
			bool Hit(const Point3 & p, const Vec3 & dirToLight, Point3 & hitPos) const;

			Basic::UniformGridSampler2D sampler;
		};
	}
}

#endif//!_ENGINE_LIGHT_AREA_LIGHT_H_