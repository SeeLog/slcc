#!/bin/zsh

assert() {
  expected="$1"
  input="$2"
  ./slcc "$input" > tmp.s
  cc -o tmp tmp.s
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert 1 'a=1; return a;'
assert 2 'b=2; return b;'
assert 2 'a=1; b=1; return a+b;'
assert 2 'a=1+1; return a;'
assert 3 'a=1; b=1; c=1; return a+b+c;'
assert 4 'a=1; b=1; c=1; d=1; return a+b+c+d;'
assert 3 'hoge=1; fuga=2; return hoge+fuga;'
assert 10 'hoge=1; fuga=2+3; piyo=4; return hoge+fuga+piyo;'
echo OK
