
using System;


namespace Borealis
{
    public class ExampleScript : MonoBehaviour
    {
        bool speed;

        public ExampleScript()
        {
            speed = true;
        }
        
        public override void Start()
        {
            InternalCalls.Log("ExampleScriptStart");
        }

        public override void Update()
        {
            InternalCalls.Log("ExampleScriptUpdate");
        }
       
    }
}
