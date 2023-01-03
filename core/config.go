package core

import (
	"errors"
	"os"
	"path/filepath"

	"github.com/pelletier/go-toml"
)

type Profile struct {
	Name string
	Path string
}

type Config struct {
	Version       int
	ActiveProfile string
	Profiles      []Profile
}

func exists(path string) bool {
	if _, err := os.Stat(path); os.IsNotExist(err) {
		return false
	}
	return true
}

func ConfigDir() (string, error) {
	home, err := os.UserHomeDir()
	if err != nil {
		return "", err
	}
	return filepath.Join(home, ".config", "todo"), nil
}

func prepare(dir, file string) error {
	var defaults = Config{
		Version:       1,
		ActiveProfile: "default",
		Profiles: []Profile{
			{Name: "default", Path: dir + "default.txt"},
		},
	}

	if !exists(dir) {
		err := os.Mkdir(dir, 0755)
		if err != nil {
			return err
		}
	}

	configFile := filepath.Join(dir, file)
	if !exists(configFile) {
		toml, err := toml.Marshal(defaults)
		if err != nil {
			return err
		}
		err = writeToFile(configFile, string(toml))
		if err != nil {
			return err
		}
	}
	return nil
}

func LoadConfig() (Config, error) {
	configDirectory, err := ConfigDir()
	if err != nil {
		return Config{}, err
	}

	err = prepare(configDirectory, "config.toml")
	if err != nil {
		return Config{}, err
	}

	var config Config

	file, err := os.ReadFile(filepath.Join(configDirectory, "config.toml"))
	if err != nil {
		return Config{}, err
	}

	err = toml.Unmarshal(file, &config)
	if err != nil {
		return Config{}, err
	}

	return config, nil
}

func UpdateConfig(config Config) error {
	configDirectory, err := ConfigDir()
	if err != nil {
		return err
	}

	toml, err := toml.Marshal(config)
	if err != nil {
		return err
	}
	return writeToFile(filepath.Join(configDirectory, "config.toml"), string(toml))
}

func GetActiveProfile() (Profile, error) {
	config, err := LoadConfig()
	if err != nil {
		return Profile{}, err
	}
	for _, profile := range config.Profiles {
		if profile.Name == config.ActiveProfile {
			return profile, nil
		}
	}
	return Profile{}, errors.New("no active profile found")
}
