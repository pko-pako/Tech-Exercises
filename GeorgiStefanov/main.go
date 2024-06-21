package main

import (
	"fmt"

	"github.com/beevik/etree"
	c "github.com/ogen-go/ogen/conv"
)

func main() {
	etree.NewDocument()
	a, _ := c.ToInt("qqq")
	fmt.Println(a)
}
