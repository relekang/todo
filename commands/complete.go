package commands

import (
	"fmt"
	"strings"

	"github.com/relekang/todo/core"
	"github.com/urfave/cli/v2"
)

var Complete = &cli.Command{
	Name:    "complete",
	Aliases: []string{"c"},
	Usage:   "complete a task",
	Action: func(cCtx *cli.Context) error {
		todos, err := core.Fetch()
		if err != nil {
			return err
		}
		todo := strings.Join(cCtx.Args().Slice(), " ")
		if todo == "" {
			todo = todos[0]
		}
		newList := []string{}
		for _, current := range todos {
			if current != todo {
				newList = append(newList, current)
			}
		}
		err = core.Update(newList)
		if err != nil {
			return err
		}
		fmt.Println("Completed task:", todo)
		return nil
	},
}
