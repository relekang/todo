package commands

import (
	"fmt"
	"strings"

	"github.com/relekang/todo/core"
	"github.com/urfave/cli/v2"
)

var Add = &cli.Command{
	Name:    "add",
	Aliases: []string{"a"},
	Usage:   "add a task",
	Flags: []cli.Flag{
		&cli.BoolFlag{
			Name:    "priority",
			Aliases: []string{"p"},
			Usage:   "Add task at the top of the list",
		},
	},
	Action: func(cCtx *cli.Context) error {
		profile, err := core.GetActiveProfile()
		if err != nil {
			return err
		}
		todos, err := core.Fetch(profile)
		if err != nil {
			return err
		}
		todo := strings.Join(cCtx.Args().Slice(), " ")
		if cCtx.Bool("priority") {
			err = core.Update(profile, append([]string{todo}, todos...))
		} else {
			err = core.Update(profile, append(todos, todo))
		}
		if err != nil {
			return err
		}
		fmt.Println("Added task", todo)
		return nil
	},
}
