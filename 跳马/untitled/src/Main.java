import java.util.*;
public class Main {
    static boolean[][] vis;  // 标记数组
    static int[] orient = {-1, 2, 1, -2, -1, -2, 1, 2, -1};  // 8个方向
    static int sum, n, m;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            // 矩阵图大小
            n = sc.nextInt();
            m = sc.nextInt();
            // 初始化标记数组，默认false
            vis = new boolean[n][m];
            // 获取起点坐标
            int x = sc.nextInt();
            int y = sc.nextInt();
            // 初始化，方案总数
            sum = 0;
            // 标记起点位置已经访问
            vis[x][y] = true;
            // 深度优先搜索：Go!
            dfs(x, y, 1);
            // 打印结果
            System.out.println(sum);
        }
    }
    public static void dfs(int x, int y, int curSum) {
        // 如果遍历完全部点，方案数 sum++，递归终止条件
        if (curSum == (n * m)) {
            sum++;
            return;
        }
        // 递归8个方向
        for (int i = 0; i < 8; i++) {
            // 获取可以到达的新方向
            int u = x + orient[i];
            int v = y + orient[i+1];
            // 剪枝条件，避免无效递归
            if (u < 0 || u >= n || v < 0 || v >= m || vis[u][v])
                continue;
            // 标记当前位置已访问
            vis[u][v] = true;
            // 继续往深处递归
            dfs(u, v, curSum+1);
            // 回溯
            vis[u][v] = false;
        }
    }
}