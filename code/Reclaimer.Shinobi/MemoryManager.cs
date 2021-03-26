using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Reclaimer.Shinobi.Internal;

namespace Reclaimer.Shinobi
{
    public class MemoryManager
    {
        public ScanManager scan = new ScanManager();
        public HookManager hook = new HookManager();
    }
}
