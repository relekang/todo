package commands

import (
	"fmt"
	"strings"

	"github.com/AlecAivazis/survey/v2"
	"github.com/relekang/todo/core"
	"github.com/urfave/cli/v2"
)

var Complete = &cli.Command{
	Name:    "complete",
	Aliases: []string{"c"},
	Usage:   "complete a task",
	Action: func(cCtx *cli.Context) error {
		profile, err := core.GetActiveProfile()
		if err != nil {
			return err
		}
		todos, err := core.Fetch(profile)
		if err != nil {
			return err
		}

		if len(todos) == 0 {
			fmt.Println("Nothing to do!")
			return nil
		}

		newList := []string{}
		toComplete := []string{}
		todo := strings.Join(cCtx.Args().Slice(), " ")
		if todo == "" {
			prompt := &survey.MultiSelect{
				Message: "Select task to complete",
				Options: todos,
			}

			err = survey.AskOne(prompt, &toComplete)
			if err != nil {
				return err
			}
		} else {
			toComplete = []string{todo}
		}

		for _, current := range todos {
			if toComplete != nil && !core.Contains(toComplete, current) {
				newList = append(newList, current)
			}
		}
		err = core.Update(profile, newList)
		if err != nil {
			return err
		}
		if len(toComplete) == 1 {
			fmt.Println("Completed task:", strings.Join(toComplete, ", "))
		} else {
			fmt.Println("Completed tasks:", strings.Join(toComplete, ", "))
		}

		return nil
	},
}
