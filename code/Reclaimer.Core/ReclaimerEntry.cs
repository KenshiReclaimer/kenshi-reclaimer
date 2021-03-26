using System;
using System.Runtime.InteropServices;
using System.Runtime.Loader;

namespace Reclaimer.Core
{
    public delegate void ReclaimerEntryFn();
    public static class ReclaimerEntry
    {
        public static void Install()
        {
            Console.WriteLine("Hello from .NET Install()");

            foreach (var ctx in AssemblyLoadContext.All)
            {
                Console.WriteLine("> Context " + ctx.Name);
                foreach (var asm in ctx.Assemblies)
                {
                    Console.WriteLine("\t> Assembly " + asm.FullName);
                }
            }
        }
        public static void Initialize()
        {
            Console.WriteLine("Hello from .NET Initialize()");
        }

        public static void Shutdown()
        {
            Console.WriteLine("Hello from .NET Shutdown()");
        }

        public static void Uninstall()
        {
            Console.WriteLine("Hello from .NET Uninstall()");
        }
    }
}
