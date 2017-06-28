#pragma once
#include <cmath>

namespace tk {
	namespace math {
		/************************************************************************************************************************
		************************************************************************************************************************/

		class Maths {
		public:
			static float cos(float x) {
				return (
					x -
					(pow(x, 2) / (float)factorial(2)) +
					(pow(x, 4) / (float)factorial(4)) -
					(pow(x, 6) / (float)factorial(6)) +
					(pow(x, 8) / (float)factorial(8))
					);
				
			}
			static float sin(float x) {
				return (
					1 -
					(pow(x, 3) / factorial(3)) +
					(pow(x, 5) / factorial(5)) -
					(pow(x, 7) / factorial(7)) +
					(pow(x, 9) / factorial(9))
					);
			}
			static int factorial(int value) {
				int temp = 1;
				for (int i = 1; i < value + 1; i++) {
					temp = temp * i;
				} return temp;
			}
			static float pow(float value, int pow) {
				float temp = value;
				for (int i = 0; i < pow; i++) {
					temp = temp * temp;
				} return temp;
			}
		};

		class Vec2 {
		public:
			Vec2() {}
			Vec2(float posx, float posy) : x(posx), y(posy) { }
			Vec2(float val) : x(val), y(val) { }
			float* operator[](int index);

			float x, y;
		};
		class Vec3 {
		public:
			Vec3() {}
			Vec3(float posx, float posy, float posz) : x(posx), y(posy), z(posz) { }
			Vec3(float val) : x(val), y(val), z(val) { }
			float* operator[](int index);

			float x, y, z;
		};
		class Vec4 {
		public:
			Vec4() {}
			Vec4(float posx, float posy, float posz, float posw) : x(posx), y(posy), z(posz), w(posw) { }
			Vec4(float val) : x(val), y(val), z(val), w(val) { }
			float* operator[](int index);

			float x, y, z, w;
		};

        /************************************************************************************************************************
		************************************************************************************************************************/

		class Mat2 {
		public:
			Mat2() {
				m_col1 = { 1, 0 };
				m_col2 = { 0, 1 };
			}
			Mat2(Vec2 col1, Vec2 col2)
				: m_col1(col1), m_col2(col2) { }
			Mat2(float val)
				: m_col1(val), m_col2(val) { }

		private:
			Vec2 m_col1, m_col2;
		};

		class Mat3 {
		public:
			Mat3();
			Mat3(Vec3 col1, Vec3 col2, Vec3 col3)
				: m_col1(col1), m_col2(col2), m_col3(col3) { }
			Mat3(float val)
				: m_col1(val), m_col2(val), m_col3(val) { }

			void SetRotateX(float angle);
			void SetRotateY(float angle);
			void SetRotateZ(float angle);
			void SetIdentity();

			Mat3 operator*(Mat3 other);
			Vec3 operator*(Vec3 other);
			Vec3 operator[](int index);

			friend Vec3 operator*(Vec3 index);

		private:
			Vec3 m_col1, m_col2, m_col3;
		};

		class Mat4 {
		public:
			Mat4();
			Mat4(Vec4 col1, Vec4 col2, Vec4 col3, Vec4 col4)
				: m_col1(col1), m_col2(col2), m_col3(col3), m_col4(col4) { }
			Mat4(float val)
				: m_col1(val), m_col2(val), m_col3(val), m_col4(val) { }

			void SetRotateX(float angle);
			void SetRotateY(float angle);
			void SetRotateZ(float angle);
			void SetIdentity();

			Mat4 operator*(Mat4 other);
			Vec4 operator*(Vec4 other);
			Vec4 operator[](int index);

			friend Vec4 operator*(Vec4 index);

			Mat4 PerspectiveFOV(double fov, double aspect, double near, double far);
		private:
			Vec4 m_col1, m_col2, m_col3, m_col4;
		};

		/************************************************************************************************************************
		************************************************************************************************************************/
	}
}