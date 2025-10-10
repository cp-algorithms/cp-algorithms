# 🌳 Trie (Prefix Tree)

A **Trie** (pronounced "try," from **reTRIEval**) is a specialized tree-like data structure primarily used to store a dynamic set of strings or associative arrays where the keys are usually strings. It allows for fast retrieval based on prefixes.

---

## 🔑 Key Concepts & Structure

A Trie organizes keys (usually words) based on their shared prefixes, making it extremely efficient for prefix-based searches.

1.  **Root Node:** The starting node, representing an empty string.
2.  **Nodes:** Each node typically represents a single character.
3.  **Edges:** The links between nodes are labeled with a character, determining the path of a word.
4.  **Children:** Each node can have multiple children, often stored in an array or a hash map, where the index/key corresponds to the next character in the sequence.
5.  **End-of-Word Marker:** A boolean flag (`isEndOfWord` or similar) within a node to indicate that the path from the root to this node forms a complete, valid word.

### Example Diagram

Consider a Trie storing the words: **"A", "TO", "TEA", "TED", "TEN", "IN", "INN"**.



Notice how the words "TEA", "TED", and "TEN" share the prefix "TE". They diverge only at the third level, saving space and improving search speed.

---

## ⚡ Advantages (Why use a Trie?)

| Feature | Description |
| :--- | :--- |
| **Speed** | Search complexity is **O(L)**, where $L$ is the length of the key. This is much faster than hash tables in the worst case, as it avoids collisions, and is independent of the number of keys, $N$. |
| **Prefix Search** | Highly efficient for finding all keys that start with a common prefix. This is the defining