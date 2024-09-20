

using System;
using System.Runtime.InteropServices;

namespace Borealis
{
    public struct Color
    {
        //Static Properties
        public static Color black => new Color(0, 0, 0, 1);
        public static Color blue => new Color(0, 0, 1, 1);
        public static Color clear => new Color(0, 0, 0, 0);
        public static Color cyan => new Color(0, 1, 1, 1);
        public static Color gray => new Color(0.5f, 0.5f, 0.5f, 1);
        public static Color green => new Color(0, 1, 0, 1);
        public static Color grey => new Color(0.5f, 0.5f, 0.5f, 1);
        public static Color magenta => new Color(1, 0, 1, 1);
        public static Color red => new Color(1, 0, 0, 1);
        public static Color white => new Color(1, 1, 1, 1);
        public static Color yellow => new Color(1, 0.92f, 0.016f, 1);


        //Properties
        public float r;
        public float g;
        public float b;
        public float a;
       
      
        public Color gamma
        {
            get
            {
                return new Color(Mathf.GammaToLinearSpace(r), Mathf.GammaToLinearSpace(g), Mathf.GammaToLinearSpace(b), a);
            }
        }
        public float grayscale
        {
            get
            {
                return 0.299f * r + 0.587f * g + 0.114f * b;
            }
        }
        public Color linear
        {
            get
            {
                return new Color(Mathf.LinearToGammaSpace(r), Mathf.LinearToGammaSpace(g), Mathf.LinearToGammaSpace(b), a);
            }
        }
        public float maxColorComponent
        {
            get
            {
                return Math.Max(r, Math.Max(g, b));
            }
        }
        

        public float this[int index]
        {
            get
            {
                if (index == 0) return r;
                if (index == 1) return g;
                if (index == 2) return b;
                if (index == 3) return a;
                throw new IndexOutOfRangeException("Invalid index for Color");
            }
            set
            {
                if (index == 0) r = value;
                else if (index == 1) g = value;
                else if (index == 2) b = value;
                else if (index == 3) a = value;
                else throw new IndexOutOfRangeException("Invalid index for Color");
            }
        }

        //Constructor
        public Color(float r, float g, float b, float a)
        {
            this.r = r;
            this.g = g;
            this.b = b;
            this.a = a;
        }

        // Public Methods
        public override string ToString()
        {
            return $"({r}, {g}, {b}, {a})";
        }

        // Static Methods
        public static Color HSVToRGB(float H, float S, float V, bool hdr = false)
        {
            if (S == 0)
            {
                // If saturation is 0, return a shade of gray.
                return new Color(V, V, V, 1);
            }

            H = H % 360; // Ensure hue is in the range [0, 360)
            float C = V * S;
            float X = C * (1 - Math.Abs((H / 60) % 2 - 1));
            float m = V - C;

            float r = 0, g = 0, b = 0;
            if (H >= 0 && H < 60)
            {
                r = C; g = X; b = 0;
            }
            else if (H >= 60 && H < 120)
            {
                r = X; g = C; b = 0;
            }
            else if (H >= 120 && H < 180)
            {
                r = 0; g = C; b = X;
            }
            else if (H >= 180 && H < 240)
            {
                r = 0; g = X; b = C;
            }
            else if (H >= 240 && H < 300)
            {
                r = X; g = 0; b = C;
            }
            else if (H >= 300 && H < 360)
            {
                r = C; g = 0; b = X;
            }

            return new Color(r + m, g + m, b + m, 1);
        }

        public static Color Lerp(Color a, Color b, float t)
        {
            return new Color(Mathf.Lerp(a.r,b.r,t), Mathf.Lerp(a.g,b.g,t), Mathf.Lerp(a.b,b.b,t), Mathf.Lerp(a.a,b.a,t));
        }

        public static Color LerpUnclamped(Color a, Color b, float t)
        {
            return new Color(Mathf.LerpUnclamped(a.r, b.r, t), Mathf.LerpUnclamped(a.g, b.g, t), Mathf.LerpUnclamped(a.b, b.b, t), Mathf.LerpUnclamped(a.a, b.a, t));
        }

        public static void RGBToHSV(Color rgbColor, out float H, out float S, out float V)
        {
            float r = rgbColor.r;
            float g = rgbColor.g;
            float b = rgbColor.b;

            float max = Math.Max(r, Math.Max(g, b));
            float min = Math.Min(r, Math.Min(g, b));
            float delta = max - min;

            // Value
            V = max;

            // Saturation
            S = (max == 0) ? 0 : delta / max;

            // Hue
            if (delta == 0)
            {
                H = 0; // Undefined
            }
            else
            {
                if (max == r)
                {
                    H = (g - b) / delta;
                }
                else if (max == g)
                {
                    H = (b - r) / delta + 2;
                }
                else
                {
                    H = (r - g) / delta + 4;
                }

                H *= 60;
                if (H < 0)
                {
                    H += 360;
                }
            }
        }

        public static Color operator +(Color a, Color b)
        {
            return new Color(a.r + b.r, a.g + b.g, a.b + b.b, a.a + b.a);
        }

        public static Color operator-(Color a, Color b)
        {
            return new Color(a.r - b.r, a.g - b.g, a.b - b.b, a.a - b.a);
        }

        public static Color operator /(Color a, float b)
        {
            return new Color(a.r / b, a.g / b, a.b / b, a.a / b);
        }

        public static Color operator *(Color b, Color a)
        {
            return new Color(a.r * b.r, a.g * b.g, a.b * b.b, a.a * b.a);
        }

        public static implicit operator Vector4(Color c)
        {
            return new Vector4(c.r, c.g, c.b, c.a);
        }

        public static implicit operator Color(Vector4 v)
        {
            return new Color(v.x, v.y, v.z, v.w);
        }
    }
}
