# minitalk

> 42 Luxembourg — Cursus Project

## What it is

`minitalk` is an inter-process communication (IPC) project using **UNIX signals**. A client sends a string to a server — but the only communication channel allowed is `SIGUSR1` and `SIGUSR2`, one bit at a time.

Every character is encoded into 8 bits and transmitted signal by signal. The server decodes and reconstructs the string in real time.

## How it works

```
Client                          Server
  |                               |
  |  sends PID to user            |
  |  encodes char → 8 bits        |
  |  SIGUSR1 = bit 0 ─────────►  |
  |  SIGUSR2 = bit 1 ─────────►  |
  |  ... (repeat x8 per char)     |
  |                               |  reconstructs char
  |  ◄───────── SIGUSR1           |  (acknowledgment)
  |  sends next char              |
```

## Build & usage

```bash
make

# Terminal 1 — start the server
./server
# prints its PID

# Terminal 2 — send a message
./client [SERVER_PID] "Hello from minitalk!"
```

## Key concepts

- **UNIX signals** — `SIGUSR1`, `SIGUSR2`, `sigaction`
- **Bitwise encoding** — transmitting data one bit at a time
- **Signal handlers** — `sa_sigaction` with `SA_SIGINFO` for sender PID
- **Synchronization** — acknowledgment signals to prevent data loss
- **Bonus** — Unicode support, server acknowledgment per character

---

*42 Luxembourg · 2024–2025 · Language: C*
