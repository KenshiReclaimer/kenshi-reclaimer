using System;
using System.Runtime.InteropServices;
using System.Runtime.Loader;
using Reclaimer.Shinobi;

namespace Reclaimer.Core
{
    public delegate void ReclaimerEntryFn();
    public static class ReclaimerEntry
    {
        [NativeGlobal]
        [ByteSignature("AA BB CC DD EE FF")]
        extern public static int Test { get; }

        [NativeFunction]
        [ByteSignature("11 ?? 22 ?? 44")]
        extern public static void DoSomethingCool();


        public static void Install()
        {
            Console.WriteLine("Hello from .NET Install()");


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
