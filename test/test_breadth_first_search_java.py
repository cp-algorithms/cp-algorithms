#!/usr/bin/env python3
"""Compile and run the Java BFS directly from the article."""
import pathlib
import re
import subprocess
import tempfile
import textwrap

source = pathlib.Path(__file__).resolve().parents[1] / "src/graph/breadth-first-search.md"
block = re.search(r"    ```java\n(.*?)    ```", source.read_text(), re.S).group(1)
block = textwrap.dedent(block)
block = re.sub(r"^ArrayList<ArrayList<Integer>> adj.*\n", "", block, flags=re.M)
block = re.sub(r"^int [ns];.*\n", "", block, flags=re.M)
program = """
import java.util.*;
public class BfsRegression {
    static int[][] run(ArrayList<ArrayList<Integer>> adj, int n, int s) {
""" + block + """
        int[] visited = new int[n];
        for (int i = 0; i < n; ++i) visited[i] = used[i] ? 1 : 0;
        return new int[][] {d, p, visited};
    }
    static void check(ArrayList<ArrayList<Integer>> adj) {
        int n = adj.size(), inf = 1000000;
        int[][] dist = new int[n][n];
        for (int i = 0; i < n; ++i) {
            Arrays.fill(dist[i], inf);
            dist[i][i] = 0;
            for (int j : adj.get(i)) dist[i][j] = 1;
        }
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
        for (int s = 0; s < n; ++s) {
            int[][] ans = run(adj, n, s);
            if (ans[1][s] != -1) throw new AssertionError("source parent");
            for (int v = 0; v < n; ++v) {
                if ((ans[2][v] != 0) != (dist[s][v] < inf)) throw new AssertionError("reachability");
                if (dist[s][v] < inf && ans[0][v] != dist[s][v]) throw new AssertionError("distance");
                if (v != s && dist[s][v] < inf) {
                    int p = ans[1][v];
                    if (!adj.get(p).contains(v) || ans[0][p] + 1 != ans[0][v])
                        throw new AssertionError("parent path");
                }
            }
        }
    }
    static ArrayList<ArrayList<Integer>> graph(int n) {
        ArrayList<ArrayList<Integer>> g = new ArrayList<>();
        for (int i = 0; i < n; ++i) g.add(new ArrayList<>());
        return g;
    }
    public static void main(String[] args) {
        ArrayList<ArrayList<Integer>> g = graph(5);
        for (int[] e : new int[][]{{0,1},{0,2},{1,4},{2,3},{3,4}}) {
            g.get(e[0]).add(e[1]); g.get(e[1]).add(e[0]);
        }
        check(g);
        Random rng = new Random(192847);
        for (int tt = 0; tt < 500; ++tt) {
            int n = 2 + rng.nextInt(19); g = graph(n);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if (i != j && rng.nextInt(5) == 0) g.get(i).add(j);
            if (tt % 2 == 0) for (int i = 0; i < n; ++i)
                for (int j : new ArrayList<>(g.get(i)))
                    if (!g.get(j).contains(i)) g.get(j).add(i);
            for (ArrayList<Integer> row : g) Collections.shuffle(row, rng);
            check(g);
        }
    }
}
"""
with tempfile.TemporaryDirectory() as directory:
    path = pathlib.Path(directory) / "BfsRegression.java"
    path.write_text(program)
    subprocess.run(["javac", str(path)], check=True, timeout=30)
    subprocess.run(["java", "-cp", directory, "BfsRegression"], check=True, timeout=30)
