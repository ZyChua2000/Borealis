using System;

namespace Borealis
{
    public struct Color32
    {
        public byte a;
        public byte b;
        public byte g;
        public byte r;

        public Color32(byte r, byte g, byte b, byte a)
        {
            this.r = r;
            this.g = g;
            this.b = b;
            this.a = a;
        }

        public byte this[int index]
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

        public override string ToString()
        {
            return $"({r}, {g}, {b}, {a})";
        }

        public static Color32 Lerp(Color32 a, Color32 b, float t)
        {
            // Create and return the new Color32
            return new Color32((byte)Mathf.Clamp(Mathf.Lerp(a.r, b.r, t), 0, 255),
                (byte)Mathf.Clamp(Mathf.Lerp(a.g, b.g, t), 0, 255), 
                (byte)Mathf.Clamp(Mathf.Lerp(a.b, b.b, t), 0, 255), 
                (byte)Mathf.Clamp(Mathf.Lerp(a.a, b.a, t), 0, 255));
        }

        public static Color32 LerpUnclamped(Color32 a, Color32 b, float t)
        {
            // Create and return the new Color32
            return new Color32((byte)Mathf.Clamp(Mathf.LerpUnclamped(a.r, b.r, t), 0, 255),
                (byte)Mathf.Clamp(Mathf.LerpUnclamped(a.g, b.g, t), 0, 255), 
                (byte)Mathf.Clamp(Mathf.LerpUnclamped(a.b, b.b, t), 0, 255), 
                (byte)Mathf.Clamp(Mathf.LerpUnclamped(a.a, b.a, t), 0, 255));
        }


        public static implicit operator Color32(Color c)
        {
            return new Color32((byte)(c.r * 255), (byte)(c.g * 255), (byte)(c.b * 255), (byte)(c.a * 255));
        }

        public static implicit operator Color(Color32 c)
        {
            return new Color(c.r / 255f, c.g / 255f, c.b / 255f, c.a / 255f);
        }
    }
}
