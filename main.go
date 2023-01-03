package main

import (
	"log"
	"os"

	"github.com/fatih/color"
	"github.com/relekang/todo/commands"
	"github.com/relekang/todo/core"
	"github.com/urfave/cli/v2"
)

func main() {
	app := &cli.App{
		Name:   "todo",
		Usage:  "simple todo cli",
		Writer: os.Stdout,
		Action: func(*cli.Context) error {
			profile, err := core.GetActiveProfile()
			if err != nil {
				return err
			}
			todos, err := core.Fetch(profile)
			if err != nil {
				println("Error: ", err)
				return err
			}
			if len(todos) == 0 {
				color.New(color.Bold).Println("Nothing to do!")
				return nil
			}
			color.New(color.Bold).Println(todos[0])
			return nil
		},
		Commands: []*cli.Command{commands.Add, commands.Complete, commands.List, commands.Profiles},
	}

	if err := app.Run(os.Args); err != nil {
		log.Fatal(err)
	}
}
