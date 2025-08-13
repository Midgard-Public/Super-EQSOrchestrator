# AGENTS.md — Super-EQSOrchestrator (UE 5.6.1)

> **Must read first.** This file defines how code agents (Codex) operate on this repo. Keep communications all-business and example-driven. No fluff.

---

## 0) Jump Table (read by task)

* **General Rules & Constants** → §1
* **APPLY mode (code editing / changes)** → §2
* **ASK mode (code interrogation / review only)** → §3
* **Comms with Stealth! (status & findings format)** → §4
* **Changelogs, Versions & Schemas** → §5
* **Style, Docs & Formatting** → §6
* **Errors, Assertions & Early-Outs** → §7
* **Logging, Metrics & Categories** → §8
* **Concurrency & Determinism** → §9
* **Anti-Monolith policy & task sizing** → §10
* **Integrations policy (StateTree, etc.)** → §11
* **Platform & UE guardrails** → §12
* **Stop conditions / timeboxing** → §13

---

## 1) General Rules & Constants

**Canonical names**

* Project: **Super-EQSOrchestrator** (always this spelling).
* Plugin folder/name: **SuperEQSOrchestrator**.
* Runtime module: **SuperEQSOrchestrator**; optional Editor module later.
* API macro prefix: **`SEQSO_API`**; C++ namespace prefix: **`SEQSO`**.

**Versioning & platforms**

* UE minimum: **5.6.1**.
* Platforms: Win64, Linux, macOS, Android, iOS; console where permitted. Use only common UE AI facilities to maximize portability.
* SemVer with CHANGELOG for every PR.

**License**

* MIT **+ Additional Terms**: (1) no resale; (2) include update link back to this repo in redistributions.

**EQS ownership**

* Game code must **not** issue EQS directly. Only this plugin may schedule/execute EQS queries and own the budget/collision policy.

**Non-negotiables**

* Deterministic tests. Never weaken tests to pass.
* No hidden edits. Always list exact file paths changed; prefer full-file replacements for large rewrites.
* UTF-8 source. No stringly-typed hacks; prefer `FName`/enums.

---

## 2) APPLY mode (code editing / changes)

**When to use:** You are landing code or docs.
**Deliverables (all required):**

1. **TITLE** line (Episode) — jokey but clear, non-violent, EQS/UE themed.
2. **GOAL** — one short paragraph.
3. **SCOPE (MUST DO)** — exact add/modify/remove paths; public API signatures; version pins/flags.
4. **CONSTRAINTS** — restate relevant global constraints.
5. **IMPLEMENTATION STEPS** — diffs or **full files** (preferred for new or heavily modified files).
6. **TESTS** — unit/integration/automation names, locations, expected outputs/logs.
7. **CLI/USAGE** (if relevant) — exact commands and exit codes.
8. **ACCEPTANCE** — build/tests/CI must be green.
9. **CHANGELOG** — prepend the exact TITLE line.
10. **PR TITLE** — exactly the TITLE line.
11. **Manual Human Verification** — explicit steps for Dan to click/run/observe.

**File limits & structure**

* Favor files ≤ **500 lines**. Split before they grow. Regions permitted (see §6).
* Keep Runtime/editor code separated by module.

---

## 3) ASK mode (code interrogation / review only)

**When to use:** Static inspection, no writes.
**Output format (strict):**

```
file:line  → finding_type  → concise_risk
Context: (≤3 lines of code or description)
Why: (1–2 lines)
Fix: (single, concrete step or link to APPLY task)
```

* No task generation unless explicitly requested.
* Cite only paths that exist in the repo. If missing, note “not found” and stop.

---

## 4) Comms with Stealth! (status & findings)

* Keep it brief, structured, and actionable.
* Start with **Answer-first** summary (≤3 bullets), then details.
* Call out **assumptions** explicitly when ambiguity exists.
* If blocked, state **what’s missing** and propose 1–2 minimal options.

---

## 5) Changelogs, Versions & Schemas

* Every PR **prepends** the Episode line to `CHANGELOG.md`.
* Include SemVer bump when public Runtime API changes or behavior meaningfully shifts.
* **Schema/IDL/config changes** must include:

  * Migration notes (old → new).
  * Versioned loaders or guards.
  * Tests that load both previous and new forms.

**Episode line template**

```
[Epic: <Series>] Episode <N> — <Jokey-but-clear tagline>: <concise scope> [vX.Y.Z]
```

---

## 6) Style, Docs & Formatting

**Follow Epic guidelines** except where overridden here. If you find a conflict, report it in ASK mode with a one-line recommendation.

**Headers — public API documentation (mandatory)**

* Every **publicly accessible** element in a header (`UCLASS`, `USTRUCT`, `UENUM`, `UFUNCTION`, `UPROPERTY`, public methods) has a **multi-block doc comment**:

  ```
  /**
   * Summary: one-sentence purpose in plain English.
   * Usage: short example or where/when to call.
   * Parameters: name — intent and units/range.
   * Returns: meaning and units/range.
   * Thread-safety: safe/unsafe; required locks.
   * Preconditions/Postconditions.
   * Errors/Logs: conditions and categories emitted.
   * Performance: notes on cost/complexity.
   */
  ```
* Names are descriptive: **what it is and what it’s for**. Avoid abbreviations in public APIs. Local variables may be compact.

**Formatting**

* **Tabs** for indentation.
* **Brace style (Allman)**:

  ```
  Statement
  {
      Statement
  }
  ```
* Use `#pragma region` consistently in both `.h` and `.cpp` to mirror structure:

  * Regions: Includes, Forward Decls, Constants, Types, Construction, Public API, Private Helpers, Logging, etc.
* Include order: public API → UE headers → local headers; forward-declare whenever possible; include in `.cpp`.

---

## 7) Errors, Assertions & Early-Outs

* **Early-out** on errors; keep control flow simple.
* **`check`** is **disallowed** (crash).
* **`ensure`** is **discouraged**; use only when something is truly wrong but survivable, and always **`ensureMsgf`** with a clear log message and recovery path.
* Pointer micro-optimizations (`if (Ptr = Source)`) only when `nullptr` is an **expected** outcome; **comment explicitly** why and what null means at that site.
* Prefer explicit guards with logged context; fail fast to the caller with status codes/results where appropriate.

---

## 8) Logging, Metrics & Categories

* Root category: **`LogSEQSO`**. Sub-categories:

  * `LogSEQSO_Query`, `LogSEQSO_Budget`, `LogSEQSO_Collision`, `LogSEQSO_Orchestrator`, `LogSEQSO_Perf`.
* Provide macros for leveled logs and structured key=value fields.
* Centralize logging configuration (verbosity, compile-time toggles) in one header.
* No `VeryVerbose` in Shipping.
* Emit **metrics hooks** (timings, counts) suitable for Unreal Insights or CSV sinks.

---

## 9) Concurrency & Determinism

* Build for concurrency from the start. Allow background work on UE task graph/thread pools where appropriate.
* Public APIs document thread-safety (see §6).
* Deterministic tests only; fixed seeds if randomness is necessary.
* Synchronization must be explicit and minimal; prefer lock-free or fine-grained locks with clear ownership comments.

---

## 10) Anti-Monolith Policy & Task Sizing

* Target ≤ **500 lines per file**. Prefer small, focused units.
* Use regions and helper types to keep readability high.
* If a file or function grows beyond comfortable size/complexity, **split it** and update includes/exports accordingly.
* **Agent warning rule:** If a change touches > **20 files** or a single file > **800 lines**, stop and propose a plan to split into smaller Episodes.

---

## 11) Integrations Policy (surgical separation)

* Core lives in the **SuperEQSOrchestrator** plugin.
* Any optional integration (e.g., **StateTree**) is a **separate, minimal plugin** that depends on core.
* No optional integration code inside the Runtime module.

---

## 12) Platform & UE Guardrails

* Keep to standard UE AI/EQS facilities; avoid platform-specific APIs.
* Runtime module contains **no editor dependencies**. Editor-only code lives in the Editor module.
* Respect UObject lifetimes & GC (no owning raw pointers to UObjects).
* Encoding: UTF-8 everywhere.

---

## 13) Stop Conditions / Timeboxing

* If a task cannot be completed within reasonable size/complexity (as indicated in §10) or required context is missing: **stop** and output a short re-plan with smaller, atomic steps.
* When uncertain, state the **assumption** you will proceed with; otherwise halt in ASK mode and request the minimal missing fact.

---

## 14) Prompt Template (verbatim; use in APPLY mode)

```
TITLE
[Epic: <Series>] Episode <N> — <Jokey-but-clear tagline>: <concise scope> [vX.Y.Z]

GOAL
<What changes achieve in one short paragraph.>

SCOPE (MUST DO)
- Paths to add/modify/remove (exact).
- Public APIs added/changed (signatures).
- Determinism/version pins.

CONSTRAINTS
- Forbidden imports/cross-layer rules.
- No hidden edits; no string-parsing hacks.

IMPLEMENTATION STEPS
- Step 1..N with exact diffs or full-file content.

TESTS
- Unit + integration (names, locations).
- Expected outputs / log snippets.

CLI/USAGE (if relevant)
- Exact commands and expected exit codes.

ACCEPTANCE
- What must be green (build/tests/CI).

CHANGELOG (prepend this exact line)
<repeat the TITLE line>

PR TITLE
<repeat the TITLE line>

Manual Human Verification
<precise steps & expected outcomes>
```

---

## 15) Example Categories & Naming (quick reference)

* Modules: `SuperEQSOrchestrator` (Runtime), `SuperEQSOrchestratorEditor` (Editor).
* Log categories: `LogSEQSO_*`.
* Types: `USeqsoOrchestrator`, `USeqsoQuery`, `FSeqsoBudget`, etc.
* Tests: `SEQSO.Basic.*`, `SEQSO.Query.*`, `SEQSO.Perf.*` (Automation framework).

---

## 16) Deviations from Epic Guidelines (current)

* Enforced **public-API doc blocks** (multi-section) in headers.
* Strong preference for **early-out** patterns and explicit guard clauses.
* **`check` disallowed**; `ensure` rare + logged via `ensureMsgf`.
* Mandatory use of **tabs** and **Allman braces** (matches Epic; reiterated here).
* Aggressive **anti-monolith** file sizing and split policy.

*If you detect any other deviation being introduced, report it in ASK mode with the smallest conforming alternative.*

---

**End of AGENTS.md**
