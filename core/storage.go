package core

import (
	"bufio"
	"os"
	"strings"
)

func readFile(filename string) ([]string, error) {
	file, err := os.Open(filename)
	if err != nil {
		return []string{}, err
	}
	defer file.Close()

	var lines []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}
	if scanner.Err() != nil {
		return nil, scanner.Err()
	}

	return lines, nil
}

func writeToFile(filename string, lines []string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	_, err = file.WriteString(strings.Join(lines, "\n"))
	return err
}

func Fetch() ([]string, error) {
	home, err := os.UserHomeDir()
	if err != nil {
		return []string{}, err
	}
	return readFile(home + "/.todo.txt")
}

func Update(lines []string) error {
	home, err := os.UserHomeDir()
	if err != nil {
		return err
	}
	return writeToFile(home+"/.todo.txt", lines)
}
