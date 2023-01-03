package commands

import (
	"errors"
	"fmt"
	"path/filepath"

	"github.com/AlecAivazis/survey/v2"
	"github.com/fatih/color"
	"github.com/relekang/todo/core"
	"github.com/urfave/cli/v2"
)

var Profiles = &cli.Command{
	Name:    "profiles",
	Aliases: []string{"p"},
	Usage:   "use profiles",
	Subcommands: []*cli.Command{
		{
			Name: "list",
			Action: func(cCtx *cli.Context) error {
				config, err := core.LoadConfig()
				if err != nil {
					return err
				}
				for _, profile := range config.Profiles {
					fmt.Println(color.New(color.Bold).Sprint(profile.Name), profile.Path)
				}
				return nil
			},
		},
		{
			Name:      "add",
			ArgsUsage: "NAME",
			Flags: []cli.Flag{
				&cli.StringFlag{
					Name:    "path",
					Aliases: []string{"p"},
					Usage:   "Path to the todo file",
				},
			},
			Action: func(cCtx *cli.Context) error {
				config, err := core.LoadConfig()
				if err != nil {
					return err
				}
				name := cCtx.Args().First()
				if name == "" {
					return errors.New("name is required")
				}
				for _, profile := range config.Profiles {
					if profile.Name == name {
						return errors.New("profile already exists")
					}
				}
				path := cCtx.String("path")
				if path == "" {
					dir, err := core.ConfigDir()
					if err != nil {
						return err
					}
					path = filepath.Join(dir, fmt.Sprintf("%s.todo", name))
				}
				profile := core.Profile{
					Name: name,
					Path: path,
				}
				config.Profiles = append(config.Profiles, profile)
				return core.UpdateConfig(config)
			},
		},
		{
			Name:      "rm",
			ArgsUsage: "NAME",
			Action: func(cCtx *cli.Context) error {
				config, err := core.LoadConfig()
				if err != nil {
					return err
				}
				profiles := []core.Profile{}
				for _, profile := range config.Profiles {
					if profile.Name != cCtx.Args().First() {
						profiles = append(profiles, profile)
					}
				}
				if len(profiles) == len(config.Profiles) {
					return errors.New("profile not found")
				}
				config.Profiles = profiles
				return core.UpdateConfig(config)
			},
		},
		{
			Name:      "activate",
			ArgsUsage: "NAME",
			Aliases:   []string{"a"},
			Action: func(cCtx *cli.Context) error {
				config, err := core.LoadConfig()
				if err != nil {
					return err
				}
				name := ""
				if len(cCtx.Args().Slice()) == 0 {
					options := []string{}
					for _, profile := range config.Profiles {
						options = append(options, profile.Name)
					}
					prompt := &survey.Select{
						Message: "Select profile to activate",
						Options: options,
					}

					err = survey.AskOne(prompt, &name)
					if err != nil {
						return err
					}
				} else {
					name = cCtx.Args().First()
				}
				config.ActiveProfile = name
				return core.UpdateConfig(config)
			},
		},
	},
}
