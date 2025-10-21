# 🎭 The Prisoner’s Dilemma

## 🧩 Introduction

The **Prisoner’s Dilemma** is a fundamental problem in **Game Theory** that explores why two rational individuals might not cooperate — even when it seems that cooperation would benefit both.

It models real-world scenarios like business competition, trust issues, and international relations.

---

## 📖 The Scenario

Two suspects, **Alice** and **Bob**, are arrested for a crime.
The police have insufficient evidence, so they offer each prisoner a deal:

| **Alice's Choice**              | **Bob's Choice**                        | **Outcome**            |
| ------------------------------- | --------------------------------------- | ---------------------- |
| Both stay silent                | Both cooperate                          | Each serves **1 year** |
| Alice betrays, Bob stays silent | Alice goes free, Bob serves **3 years** |                        |
| Bob betrays, Alice stays silent | Bob goes free, Alice serves **3 years** |                        |
| Both betray                     | Each serves **2 years**                 |                        |

---

## 🎯 Payoff Matrix

|                               | **Bob: Cooperate (Silent)** | **Bob: Defect (Betray)** |
| ----------------------------- | --------------------------- | ------------------------ |
| **Alice: Cooperate (Silent)** | (-1, -1)                    | (-3, 0)                  |
| **Alice: Defect (Betray)**    | (0, -3)                     | (-2, -2)                 |

Each pair shows **(Alice’s years, Bob’s years)** — smaller is better.

---

## 🧠 Analysis

* If Alice thinks Bob will **cooperate**, she should **betray** (0 years vs 1 year).
* If Alice thinks Bob will **betray**, she should **still betray** (2 years vs 3 years).
* The same logic applies for Bob.

Thus, **betrayal (defection)** is the *dominant strategy* for both.

However, this leads to **worse outcomes** (2 years each) than mutual cooperation (1 year each).

---

## ⚖️ Nash Equilibrium

A **Nash Equilibrium** occurs when no player can improve their outcome by changing their choice, given the other’s decision.

* Here, both **defecting** (betrayal) is a Nash equilibrium — even though it’s not optimal for either.

---

## 🌍 Real-World Applications

* **Business competition:** Companies undercut prices to gain market share.
* **Environmental policy:** Countries overuse resources instead of cooperating.
* **Cybersecurity:** Organizations hoard threat intelligence rather than share it.

---

## 💡 Key Takeaways

| Concept               | Meaning                                                                    |
| --------------------- | -------------------------------------------------------------------------- |
| **Dominant Strategy** | A move that’s best regardless of what others do                            |
| **Nash Equilibrium**  | A stable outcome where no one benefits from changing their choice          |
| **Pareto Optimal**    | An outcome where no one can be better off without making someone worse off |

---

## 🧩 Summary

* The rational choice (defect) leads to a suboptimal outcome.
* Cooperation can lead to better collective results.
* The dilemma reveals the tension between **individual rationality** and **collective benefit**.

---

📚 **Reference:**

* J. Nash (1950), *Equilibrium Points in N-Person Games*, PNAS.
* A. Rapoport & A. Chammah (1965), *Prisoner's Dilemma: A Study in Conflict and Cooperation*.
