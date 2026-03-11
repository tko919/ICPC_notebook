# 使い⽅: sh hash.sh -> コピペ -> Ctrl + D
# コメント・空⽩・改⾏を削除して md5 でハッシュする
g++ -dD -E -P -fpreprocessed - | tr -d '[:space:]' | md5sum | cut -c-6