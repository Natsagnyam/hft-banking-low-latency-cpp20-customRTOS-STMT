Since you want to include the technical details on how you bypass the kernel's scheduler, let's refine the `README.md` to include a specific section on **CPU Pinning and Isolation**. This explains the mechanism behind how you effectively silence the "OS noise."

Here is the updated `README.md` content:

---

# HFT Banking Engine (Custom RTOS Scheduler Implementation)

## Overview

This engine is designed for ultra-low latency execution by implementing a **Custom RTOS-style Scheduler** running on top of Linux. By bypassing standard OS kernel scheduling, we eliminate interrupt jitter and context-switching overhead, ensuring deterministic performance for banking transaction processing.

## The Problem: Kernel Noise

Standard Linux kernels are optimized for throughput and fairness, not latency. "Kernel noise"—caused by OS background tasks, interrupt handling, and preemptive scheduling—introduces micro-delays that are fatal to HFT strategies.

## The Solution: Custom RTOS Scheduler

Our architecture moves critical tasks into a deterministic execution loop, pinning them to isolated CPU cores.

### Key Architectural Pillars

* **CPU Pinning (Affinity)**: We use `pthread_setaffinity_np` to bind our producer and consumer threads to specific physical cores. This prevents the OS from migrating our tasks and destroying our L1/L2 cache locality.
* **Thread Isolation**: By isolating these cores via Linux boot parameters (e.g., `isolcpus`), we ensure the kernel scheduler does not schedule *any* other processes on these cores.
* **Atomic Memory Alignment**: We use explicit padding to ensure all control structures (`producer_ctrl`, `consumer_ctrl`) span distinct 64-byte cache lines, preventing **False Sharing**.
* **Lock-Free Communication**: We utilize memory barriers (`memory_order_acquire`/`release`) and ring buffers instead of mutexes, ensuring an **Atomic Battle-Free** environment.

### Scheduling Logic

Unlike the standard CFS (Completely Fair Scheduler), our `run_scheduler()` acts as a tight polling loop:

1. **Poll**: Continuously check the `tail` pointer of the ring buffer.
2. **Process**: Execute the trading logic immediately upon data arrival.
3. **No Context Switch**: Because the thread never enters a "Wait" state, it never triggers a kernel context switch, remaining exclusively in user-space.

---

## Build & Test

1. **Compilation**: Built with `g++ -O3 -march=native` to leverage hardware-specific instructions.
2. **Alignment Verification**: `test_cache_alignment` confirms memory isolation.
3. **Latency Profiling**: `benchmark_latency` provides real-time feedback on execution determinism.

---

### Why this structure is effective:

* **Educational Clarity**: It explains to a peer or recruiter exactly *how* you are bypassing the kernel (isolcpus + affinity).
* **Technical Credibility**: Mentioning specific techniques like `isolcpus` and `pthread_setaffinity_np` demonstrates that you understand the low-level interactions between code and hardware.

