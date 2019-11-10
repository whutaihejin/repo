package main

import (
	"fmt"
	"io"
	"io/ioutil"
	"net/http"
	"os"
	"time"
)

func main() {
	start := time.Now()
	ch := make(chan string)
	for _, url := range os.Args[1:] {
		go fetch(url, ch) // start a goroutine
	}
	for range os.Args[1:] {
		fmt.Println(<-ch) // receive from channel ch
	}
	fmt.Printf("%dms elapsed\n", time.Since(start).Milliseconds())
}

func fetch(url string, ch chan<- string) {
	start := time.Now()
	reply, err := http.Get(url)
	if err != nil {
		ch <- fmt.Sprint(err) // send to channel ch
		return
	}
	bytes, err := io.Copy(ioutil.Discard, reply.Body)
	reply.Body.Close()
	if err != nil {
		ch <- fmt.Sprintf("while reading %s: %v", url, err)
		return
	}
	ms := time.Since(start).Milliseconds()
	ch <- fmt.Sprintf("%dms %7d %s", ms, bytes, url)
}
