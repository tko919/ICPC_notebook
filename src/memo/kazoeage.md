## 数列一覧
- 第一種スターリング数 $c(n,k)$ : $1,\ldots,n$ の順列で巡回置換 $k$ 個に分割できるものの個数
    - $c(n,k)=c(n-1,k-1)+(n-1)c(n-1,k)$
    - $[x^k]x(x+1)\cdots(x+n-1)=c(n,k)$
    - $\sum_k 2^kc(n,k)=(n+1)!,\sum_k (-1)^k c(n,k)=0$
- 第二種スターリング数 $S(n,k)$ : $1,\ldots,n$ を $k$ 個の区別しない集合に分割する方法の数
    - $S(n,k)=S(n-1,k-1)+kS(n-1,k)$
    - $S(n,k)={1 \over k!}\sum_{m=1}^k (-1)^{k-m}\binom{k}{m}m^n$
- ベル数 $B_n$ : $1,\ldots,n$ をいくつかの集合に分割する方法の数
    - $\exp(\exp x-1)=\sum_n B_n {x^n \over n!}$
    - $B_{n+1}=\sum_{k=0}^n \binom{n}{k}B_k$ 
- カタラン数 $C_n$ : 長さ $2n$ のvalidなカッコ列の個数
    - $C_n={1 \over n}\binom{2n}{n}=[x^n]{1-\sqrt{1-4x} \over 2x}$
    - $C_{n+1}={2(2n+1)\over n+2}C_n=\sum_{k=0}^n C_kC_{n-k}$
- モンモール数 $a_n$ : $1,\ldots,n$ の順列で $p_i \neq i$ となる個数
    - $a_n=(n-1)(a_{n-1}+a_{n-2}), a_n=na_{n-1}+(-1)^n$
- 分割数 $P_n$ : $n$ を正整数の和で表す方法の数
    - $\sum_n P_n x^n=\prod_{n \geq 1} (1-x^n)=\sum_{n=-\infty}^\infty (-1)^n x^{n(3n+1)/2}$

## FPS公式
$[x^n] {1 \over (1-x)^d}=\binom{n+d-1}{n}$ 

$[x^n] {1 \over \sqrt{1-4x}}=\binom{2n}{n}$ 

${1 \over k}(\exp x-1)^k=\sum_n S(n,k){x^n \over n!}$ (第二種スターリング数)

${\exp(-x) \over 1-x}=\sum_n a_n{x^n \over n!}$ (モンモール数)

$[x^n] C(x)^k= {k \over n+k} \binom{2n+k-1}{n}$ 


## Lagrange反転
$F(x),G(x) \in \mathbb{C}(x) \mbox{ s.t. } F(G(x))=G(F(x))=x$ について、 $[x^n]G(x)=\frac{1}{n}[x^{n-1}]\lbrace \frac{x}{F(x)} \rbrace^n$ 

## LGV lemma
$\lbrace a_1,\ldots,a_n \rbrace$ を始点集合、$\lbrace b_1,\ldots,b_n \rbrace$ を終点集合とするDAGがあり、「 $i<j$ なら $a_i \to b_j$ のpathと $a_j \to b_i$ のpathは必ず交差する」と仮定する。
このとき、互いに交わらない $a_i \to b_i$ のpathの組の個数は、 $a_i \to b_j$ のpathの個数を $c_{ij}$ として $\det(c_{ij})$ に等しい。
