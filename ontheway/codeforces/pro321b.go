package main

import (
	"fmt"
	"sort"
)

var (
	n,m,i,j int
	atk,def,fox []int
)	

func main(){
	fmt.Scan(&n,&m)
	var temp string
	for i:=0;i<n;i++{
		fmt.Scan(&temp,&j)
		if temp == "ATK" {
			atk = append(atk,j)
		} else {
			def = append(def,j)
		}
	}
	for i:=0;i<m;i++ {
		fmt.Scan(&j)
		fox=append(fox,j)
	}
	sort.Int(def)
	sort.Int(atk)
	sort.Int(fox)
	j=0
	for _,r := range def {
		for j < len(fox) && fox[j] <= r {
			j++
		}
		if j < len(fox) {

