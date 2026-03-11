## 燃やす埋める
| 変形前の制約 | 変形後の制約 |
| --- | --- |
| $x$ が $0$ のとき $z$ 失う | $(x, T, z)$ |
| $x$ が $0$ のとき $z$ 得る | 無条件で $z$ 得る; $(S, x, z)$ |
| $x$ が $1$ のとき $z$ 失う | $(S, x, z)$ |
| $x$ が $1$ のとき $z$ 得る | 無条件で $z$ 得る; $(x, T, z)$ |
| $x, y$ がともに $0$ のとき $z$ 得る | 無条件で $z$ 得る; $(S, w, z), (w, x, \infty), (w, y, \infty)$ |
| $x, y$ がともに $1$ のとき $z$ 得る | 無条件で $z$ 得る; $(w, T, z), (x, w, \infty), (y, w, \infty)$ |

## LP双対
$\max c^Tx \mbox{ s.t. } Ax=b,x \geq 0$ と $\min b^Ty \mbox{ s.t. } A^Ty \geq c$ の最適解は、存在すれば一致。

## Erd&ouml;s-Gallai Theorem
$\lbrace d_i \rbrace$ :単調減少列が $n$ 頂点の木の次数列となるためには、「$\sum d_i$ が偶数かつ $\forall k,\sum_{i \leq k} d_i \leq k(k-1)+\sum_{i>k} \min(d_i,k)$ 」が必要十分。

## Gale-Ryser Theorem
$\lbrace a_i \rbrace,\lbrace b_i \rbrace$ :単調減少列が $n \times n$ の01 matrixの各行各列の総和の列となるためには、「$\sum a_i=\sum b_i$ かつ $\forall k,\sum_{i \leq k} a_i \leq \sum \min(b_i,k)$ 」が必要十分。