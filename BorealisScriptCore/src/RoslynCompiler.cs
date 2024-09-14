// File: RoslynCompiler.cs
using System;
using System.IO;
using System.Runtime.CompilerServices;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
namespace Borealis
{
    public class RoslynCompiler
    {
        
        public RoslynCompiler()
        {
            GameObject Object = new GameObject("name");
            Transform transform = Object.AddComponent<Transform>();
            SpriteRenderer sr = Object.AddComponent<SpriteRenderer>();
            Color color = new Color ( 0.5f, 0.5f, 0.5f, 1.0f );
            sr.Color = color;

            //Vector3 position = new Vector3(1, 2, 3);
            //transform.position = position;           
        }

        /*!***********************************************************************
            \brief
                Compiles a C# code into an assembly.
            \param code
                The C# code to compile.
            \param assemblyName
                The name of the assembly to create.
        *************************************************************************/
        public byte[] CompileCode(string code, string assemblyName)
        {
            var syntaxTree = CSharpSyntaxTree.ParseText(code);
            CSharpCompilation compilation = CSharpCompilation.Create(
                assemblyName,
                new[] { syntaxTree },
                new[] { MetadataReference.CreateFromFile(typeof(object).Assembly.Location) },
                new CSharpCompilationOptions(OutputKind.DynamicallyLinkedLibrary));

            using (var dllStream = new MemoryStream())
            {
                var emitResult = compilation.Emit(dllStream);
                if (!emitResult.Success)
                {
                    // emitResult.Diagnostics
                }
                return dllStream.ToArray();
            }

        }
    }
}
