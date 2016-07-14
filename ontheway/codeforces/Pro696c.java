import java.util.Scanner;

public class Pro696c {
  static int div = 1000000007;

  static long[][] ans1, now1, resans1 = new long[2][2], resnow1 = new long[2][2], temp;

  static void mul(long[][] a, long[][] b, long[][] res) {
    int i, j, r;
    res[0][0] = res[0][1] = res[1][0] = res[1][1] = 0;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++) {
        for (r = 0; r < 2; r++) {
          res[i][j] += a[i][r] * b[r][j] % div;
          res[i][j] %= div;
        }
      }
    }
  }

  static void mul_ans1(long[][] a, long[][] b) {
    resans1[0][0] = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % div;
    resans1[0][1] = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % div;
    resans1[1][0] = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % div;
    resans1[1][1] = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % div;
    temp = ans1;
    ans1 = resans1;
    resans1 = temp;
  }

  static void mul_now1(long[][] a, long[][] b) {
    resnow1[0][0] = (a[0][0] * b[0][0] + a[0][1] * b[1][0]) % div;
    resnow1[0][1] = (a[0][0] * b[0][1] + a[0][1] * b[1][1]) % div;
    resnow1[1][0] = (a[1][0] * b[0][0] + a[1][1] * b[1][0]) % div;
    resnow1[1][1] = (a[1][0] * b[0][1] + a[1][1] * b[1][1]) % div;
    temp = now1;
    now1 = resnow1;
    resnow1 = temp;
  }



  static long[][] init(long a, long b, long c, long d) {
    long[][] p = new long[2][2];
    p[0][0] = a;
    p[0][1] = b;
    p[1][0] = c;
    p[1][1] = d;
    return p;
  }

  static long ans = 2, now = 2;
  static long rev = 500000004;

  static void get1(long p) {
    now1 = ans1;
    ans1 = init(1, 0, 0, 1);
    int i;
    now = ans;
    ans = 1;
    while (p > 0) {
      if ((p & 1) > 0) {
        ans *= now;
        ans %= div;
        mul_ans1(ans1, now1);
      }
      now *= now;
      now %= div;
      mul_now1(now1, now1);
      p >>= 1;
    }
    /*
    cout << ans1.p[1][0] << "/" << ans << endl;
    return;
    cout << ans << endl;
    cout << ans1.p[0][0] << " " << ans1.p[0][1]  << " "
         << ans1.p[1][0] << " " << ans1.p[1][1] << endl;
    */
  }

  public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    int n = scan.nextInt();
    ans1 = init(0, 2, 1, 1);
    for (int i = 0; i < n; i++) {
      long tmp = scan.nextLong();
      get1(tmp);
    }
    long a = ans1[1][1] - ans1[1][0];
    if (a < 0) {
      a += div;
    }
    a = a * rev % div;
    System.out.print(a);
    System.out.print("/");
    System.out.println(ans * rev % div);
  }
}
