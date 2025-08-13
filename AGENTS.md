AGENTS_SPEC
===========

```yaml
AGENTS_SPEC: "SEQSO-AGENTS"
SPEC_VERSION: "1.0.1"
PROJECT:
  NAME: "Super-EQSOrchestrator"
  UE_MIN: "5.6.1"
  MODULES:
    RUNTIME: "SuperEQSOrchestrator"
    EDITOR: "SuperEQSOrchestratorEditor"
  API_PREFIX: "SEQSO_API"
  NAMESPACE_PREFIX: "SEQSO"
  VERSION_SEMVER: "0.1.0"
  PLATFORMS: ["Win64","Linux","Mac","Android","IOS"]
LICENSE:
  BASE: "MIT"
  ADDITIONAL_TERMS:
    - "No resale of standalone Software"
    - "Include update link https://github.com/YOURORG/SuperEQSOrchestrator in redistributions"
CONTRACTS:
  PR_TITLE_EQUALS_EPISODE: true
  CHANGELOG_PREPEND_EPISODE: true
  DETERMINISTIC_TESTS_ONLY: true
```

INDEX (read-by-task)

APPLY mode (code changes) → §APPLY

ASK mode (interrogation) → §ASK

PR/Changelog contract → §PR

Style & Formatting → §STYLE

Errors & Early-Outs → §ERRORS

Logging & Metrics → §LOGGING

Concurrency & Determinism → §CONCURRENCY

Anti-Monolith thresholds → §ANTI_MONOLITH

Integrations policy → §INTEGRATIONS

Platform & UE guardrails → §PLATFORM

Stop/Timebox conditions → §STOP

Prompt templates → §TEMPLATES

Naming quick reference → §NAMING

Deviations vs Epic → §DEVIATIONS

DIRECTIVES (stable IDs)
General / Non-negotiables

D001 MUST: No hidden edits; list exact paths changed; prefer full-file replacements for large rewrites.

D002 MUST: Deterministic tests; never weaken tests to pass.

D003 MUST: UTF-8 source; avoid stringly-typed hacks; prefer FName/enums.

D004 MUST: Public headers require multi-block doc comments (see §STYLE.DOCS).

D005 MUST: Use spaces (4) for indentation and Allman brace style in code.

D006 MUST: Report assumptions explicitly when proceeding under ambiguity.

D007 MUST: Keep Runtime and Editor code in separate modules.

EQS Ownership

D020 MUST: Game code MUST NOT issue EQS directly. Only this plugin may schedule/execute EQS and own budget/collision policy.

Anti-monolith

D030 SHOULD: Target ≤ 500 lines per file.

D031 MUST: If a change touches > 20 files OR any single file > 800 lines post-change → STOP and propose split plan.

D032 SHOULD: Prefer many small, focused units; use regions for structure.

Formatting & Structure

D040 MUST: Use #pragma region consistently in .h and .cpp with mirrored region names.

D041 MUST: Include order: public API → UE headers → local headers; forward-declare where possible; include in .cpp.

D042 SHOULD: Descriptive names for classes/functions/params; local variables may be compact.

Errors & Assertions

D050 MUST: Early-out on error paths; keep control flow simple.

D051 MUST NOT: Use check (crash).

D052 SHOULD NOT: Use ensure; when unavoidable, use ensureMsgf with clear logs and recovery path.

D053 MUST: Pointer optimizations (if (Ptr = Source)) only when nullptr is expected; add comment explaining meaning of nullptr.

Logging & Metrics

D060 MUST: Root log category LogSEQSO; sub-categories LogSEQSO_Query, LogSEQSO_Budget, LogSEQSO_Collision, LogSEQSO_Orchestrator, LogSEQSO_Perf.

D061 MUST: Centralize logging macros and verbosity configuration in a single header.

D062 MUST NOT: Use VeryVerbose in Shipping.

D063 SHOULD: Emit metrics hooks (timings/counts) suitable for Insights/CSV.

Concurrency & Determinism

D070 SHOULD: Build for concurrency (UE task graph/thread pools) with explicit thread-safety notes in public APIs.

D071 MUST: Tests remain deterministic; fixed seeds if randomness is required.

D072 SHOULD: Prefer lock-free or fine-grained locking with ownership comments.

Integrations (surgical separation)

D080 MUST: Optional integrations (e.g., StateTree) live as separate plugins depending on core. No optional code inside Runtime.

Platform & UE Guardrails

D090 MUST: Use only common UE AI facilities; avoid platform-specific APIs.

D091 MUST: Respect UObject lifetimes & GC; no owning raw pointers to UObjects.

Stop / Timebox

D100 MUST: If task scope exceeds thresholds (§ANTI_MONOLITH) or required context is missing, STOP and output a re-plan with atomic steps.

§APPLY — APPLY mode (code editing)
REQUIRED OUTPUT (in this order):

TITLE (Episode line; non-violent, EQS/UE-themed; include [vX.Y.Z])

GOAL (≤1 paragraph)

SCOPE (exact add/modify/remove paths; public API signatures; version pins/flags)

CONSTRAINTS (restate relevant D-IDs)

IMPLEMENTATION STEPS (diffs or full files; full files preferred for heavy rewrites)

TESTS (unit/integration names, locations, expected outputs/logs)

CLI/USAGE (commands and expected exit codes) — if relevant

ACCEPTANCE (what must be green)

CHANGELOG (prepend exact TITLE line)

PR TITLE (exact TITLE line)

Manual Human Verification (click/run/expect steps)

§ASK — ASK mode (interrogation; no writes)
Use this exact finding format:

```vbnet
file:line  → finding_type  → concise_risk
Context: (≤3 lines)
Why: (≤2 lines)
Fix: (single concrete step or APPLY-reference)
```
Rules:

No task generation unless explicitly requested.

Cite only existing paths; if missing, say “not found” and STOP.

§PR — PR/Changelog Contract
PR title == Episode line.

Prepend Episode line to CHANGELOG.md.

Manual Human Verification required in PR body.

Each PR must list exact file paths changed.

§STYLE — Style, Docs & Formatting
DOCS:

Public API elements in headers (UCLASS, USTRUCT, UENUM, UFUNCTION, UPROPERTY, public methods) require multi-block comments with these labeled fields:

Summary, Usage, Parameters (name→intent/range/units), Returns, Thread-safety, Preconditions, Postconditions, Errors/Logs, Performance.
CODE:

Spaces (4) for indentation; Allman braces:

```pgsql
Statement
{
    Statement
}
```
Use #pragma region in .h and .cpp with mirrored structure.

Names: describe what and what-for; avoid abbreviations in public APIs.

§ERRORS — Errors, Assertions & Early-Outs
Early-out on errors; prefer explicit guard clauses.

check forbidden; ensure rare and only via ensureMsgf with logs + recovery.

Pointer optimizations only when nullptr expected; add comment.

§LOGGING — Logging & Metrics
Categories: LogSEQSO, LogSEQSO_Query, LogSEQSO_Budget, LogSEQSO_Collision, LogSEQSO_Orchestrator, LogSEQSO_Perf.

Centralize macros/configuration; forbid VeryVerbose in Shipping.

Provide metric hooks (Insights/CSV).

§CONCURRENCY — Concurrency & Determinism
Concurrency allowed; document thread-safety in public APIs.

Deterministic tests with fixed seeds if randomness is used.

Prefer minimal synchronization with clear ownership.

§ANTI_MONOLITH — Anti-Monolith Policy & Sizing
Target ≤ 500 lines/file.

STOP if > 20 files touched or any single file > 800 lines; propose split.

Use regions and helper types to maintain readability.

§INTEGRATIONS — Optional Integrations
Separate, tiny integration plugins (e.g., StateTree) depending on core.

No optional integration code inside Runtime module.

§PLATFORM — Platform & UE Guardrails
Standard UE AI/EQS facilities; cross-platform friendly.

Runtime-only module free of editor dependencies.

Respect UObject lifetimes & GC.

§STOP — Stop/Timebox Conditions
If scope too large or context missing → STOP with a smaller, atomic plan.

Report assumptions explicitly if proceeding.

§TEMPLATES — Prompt & Finding Templates
APPLY_PROMPT_TEMPLATE (verbatim)

```pgsql
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
ASK_FINDING_FORMAT (verbatim)

```vbnet
file:line  → finding_type  → concise_risk
Context: (≤3 lines)
Why: (≤2 lines)
Fix: (single concrete step or APPLY-reference)
```
§NAMING — Quick Reference
Modules: SuperEQSOrchestrator (Runtime), SuperEQSOrchestratorEditor (Editor).

Log categories: LogSEQSO*, see §LOGGING.

Types: USeqsoOrchestrator, USeqsoQuery, FSeqsoBudget, etc.

Tests: SEQSO.Basic., SEQSO.Query., SEQSO.Perf.* (Automation).

§DEVIATIONS — From Epic Guidelines
Mandatory public-API multi-block docs in headers.

Strong preference for early-outs and explicit guards.

check forbidden; ensure rare with ensureMsgf.

Spaces (4) + Allman brace style reiterated.

Aggressive anti-monolith split policy and stop thresholds.

END OF FILE
