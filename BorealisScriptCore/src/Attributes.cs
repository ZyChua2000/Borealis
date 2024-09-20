using System;
namespace Borealis
{
    public class SerializeField : Attribute
    {
    }
    public class HideInInspector : Attribute
    {
    }
    public class Header : Attribute
    {
        public string header;
        public Header(string header)
        {
            this.header = header;
        }
    }
}
