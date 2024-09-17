

namespace Borealis
{
    public class SpriteRenderer : Component
    {
        //public int childCount;
        public Color Color
        {
            get
            {
                InternalCalls.SpriteRendererComponent_GetColor(gameObject.GetInstanceID(), out Color color);
                return color;
            }
            set
            {
                InternalCalls.SpriteRendererComponent_SetColor(gameObject.GetInstanceID(), ref value);
            }
        }
    }
}
