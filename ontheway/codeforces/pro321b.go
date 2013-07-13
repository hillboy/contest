package main

import (
	"fmt"
	"sort"
)

var (
	n, m, i, j    int
	atk, def, fox []int
)

func killAll() int {
	var cp []int
	cp = append(cp, fox...)
	i := 0
	for j := 0; j < len(def); j++ {
		for i < len(cp) {
			if cp[i] > def[j] {
				cp[i] = 0
				break
			}
			i += 1
		}
		if i == len(cp) {
			return 0
		}
	}
	ans := 0
	i = 0
	for j := 0; j < len(atk); j++ {
		for i < len(cp) {
			if cp[i] >= atk[j] {
				ans += cp[i] - atk[j]
				cp[i] = 0
				break
			}
			i += 1
		}
		if i == len(cp) {
			return 0
		}
	}
	for i := 0; i < len(cp); i++ {
		ans += cp[i]
	}
	return ans
}

func onlyatk() int {
	ans := 0

	for i := 0; i < len(atk); i++ {
		if i >= len(fox) {
			return ans
		}
		now := 0
		for j := 0; j <= i; j++ {
			now += fox[len(fox)-j-1] - atk[j]
		}
		if now > ans {
			ans = now
		}
	}
	return ans
}

func main() {
	fmt.Scan(&n, &m)
	var temp string
	for i := 0; i < n; i++ {
		fmt.Scan(&temp, &j)
		if temp == "ATK" {
			atk = append(atk, j)
		} else {
			def = append(def, j)
		}
	}
	for i := 0; i < m; i++ {
		fmt.Scan(&j)
		fox = append(fox, j)
	}
	sort.Ints(def)
	sort.Ints(atk)
	sort.Ints(fox)
	a := killAll()
	b := onlyatk()
	if a>b {
		fmt.Println(a)
	} else {
		fmt.Println(b)
	}
}
