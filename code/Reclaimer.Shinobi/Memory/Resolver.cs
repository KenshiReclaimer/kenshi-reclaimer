using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace Reclaimer.Shinobi.Memory
{
    public static partial class Resolver
    {
        public static bool Initialized = false;

        public static void Initialize()
        {
            if (Initialized) return;

            var module = Process.GetCurrentProcess().MainModule;
            var scanner = new SigScanner(module);

            InitializeMemberFunctions(scanner);
            InitializeStaticAddresses(scanner);

            Initialized = true;
        }

        public static void Initialize(IntPtr moduleCopy)
        {
            if (Initialized) return;

            var module = Process.GetCurrentProcess().MainModule;
            var scanner = new SigScanner(module, moduleCopy);

            InitializeMemberFunctions(scanner);
            InitializeStaticAddresses(scanner);

            Initialized = true;
        }
    }
}
