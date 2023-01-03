package commands

import (
	"fmt"

	"github.com/relekang/todo/core"
	"github.com/urfave/cli/v2"
)

var List = &cli.Command{
	Name:    "list",
	Aliases: []string{"l"},
	Usage:   "list tasks",
	Flags: []cli.Flag{
		&cli.StringFlag{
			Name:    "format",
			Aliases: []string{"f"},
			Usage:   "Format of the output",
			Value:   "text",
		}},
	Action: func(cCtx *cli.Context) error {
		profile, err := core.GetActiveProfile()
		if err != nil {
			return err
		}
		todos, err := core.Fetch(profile)
		if err != nil {
			return err
		}
		switch cCtx.String("format") {
		case "xbar":
			if len(todos) == 0 {
				fmt.Println("Nothing to do!")
				return nil
			}
			fmt.Println(todos[0])
			fmt.Println("---")
			for i, todo := range todos {
				if i > 0 {
					fmt.Println(todo)
				}
			}

		case "text":
			if len(todos) == 0 {
				fmt.Println("Nothing to do!")
				return nil
			}
			fmt.Println("Current:", todos[0])
			for i, todo := range todos {
				if i > 0 {
					fmt.Println(todo)
				}
			}
		}
		return nil
	},
}
