package main

import (
	"fmt"
)

var (
	a, b, x, y int
	s          string
)

var xx = []int{0}
var yy = []int{0}

func make2(a, b, delta int) int {
	if delta == 0 {
		if a == b {
			return -1
		}
		return -2
	}
	if (b-a)%delta != 0 || (b-a)/delta < 0 {
		return -2
	}
	return (b - a) / delta
}

func main() {
	fmt.Scan(&a, &b, &s)
	for _, i := range s {
		switch i {
		case 'U':
			y += 1
		case 'D':
			y -= 1
		case 'L':
			x -= 1
		case 'R':
			x += 1
		}
		xx = append(xx,x)
		yy = append(yy,y)
	}
	for i, _ := range xx {
		aa := make2(xx[i], a, x)
		bb := make2(yy[i], b, y)
		if aa == -2 || bb == -2 {
			continue
		}
		if (aa == -1) || (bb == -1) || (aa == bb) {
			fmt.Println("Yes")
			return
		}
	}
	fmt.Println("No")
}
