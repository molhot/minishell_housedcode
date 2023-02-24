#!/bin/bash

assert() {
  # テストしようとしている内容をprint
	printf '%-30s:' "\"$1\""

	# bashの出力をcmpに保存
	echo -n -e "$1" | bash >cmp 2>&-
	# bashのexit statusをexpectedに代入
	expected=$?
	# minishellの出力をoutに保存
	echo -n -e "$1" | ./minishell >out 2>&-
	# minishellのexit statusをactualに代入
	actual=$?

	# bashとminishellの出力を比較
	diff cmp out >/dev/null && echo -n '  diff OK' || echo -n '  diff NG'

	# bashとminishellのexit statusを比較
	if [ "$actual" = "$expected" ]; then
		echo -n '  status OK'
	else
		echo -n "  status NG, expected $expected but got $actual"
	fi
	echo
}

#. Generate Executable
cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

# Empty line (EOF)
assert ''
assert '/bin/pwd'
assert '/bin/echo'
assert 'pwd'
assert 'ls'
assert './a.out'

assert 'echo hoge'
# redirect
assert 'cat < in'
assert '< in cat'

assert 'hogehoge'

assert 'echo hello | cat'
assert 'echo hello | cat | cat < in | cat < new.txt'
assert 'echo hello | ls | pwd | cd ../ | ls '
assert 'echo hello | cat < $PATH'
assert 'echo hello | cat < new1.txt'
assert 'echo hello | cat < new1.txt | cat < new1.txt | cat < new1.txt | cat < new1.txt'
# pipe
assert 'echo hoge | cat'
assert 'echo hoge | cat | grep hoge'
assert 'echo hoge | cat | grep "hoge"'

# expand
export hoge=HOGE
assert 'echo $hoge'
assert 'echo $$hoge'

