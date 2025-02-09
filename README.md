# TMDB CLI Tool

This project is a simple Command Line Interface (CLI) tool that interacts with the TMDB API. The tool retrieves information about movies, including popular, top-rated, upcoming, and currently playing movies.

## Features

- Fetch and display a list of movies by type:
  - `playing` — currently playing movies
  - `popular` — popular movies
  - `top` — top-rated movies
  - `upcoming` — upcoming movies
- Error handling for missing or invalid arguments
- Display movie title, release date, overview, and rating

## Prerequisites

!THIS PROJECT IN WINDOWS ONLY!

To run it, you will need:

- A C++ compiler (e.g., GCC, Visual Studio)
- [cURL](https://curl.se/) library for making HTTP requests
- [nlohmann/json](https://github.com/nlohmann/json) for JSON parsing
- A TMDB API key and access token (see below)

## Setup

1. Clone this repository:

    ```cmd
    git clone https://github.com/raogpip/tmdb-cli-tool.git
    cd tmdb-cli-tool
    ```

2. Set up your TMDB API key and access token as environment variables. In your `.env` file (or system environment), add the following:

    ```
    TMDB_API_KEY=your_api_key_here
    TMDB_ACCESS_TOKEN=your_access_token_here
    ```

3. Build the project using your preferred C++ build tool (e.g., Visual Studio, CMake, etc.).
  
4. Run the program:

    ```cmd
    .\tmdb-cli-tool --type "popular"
    ```

## Usage

To use the CLI tool, run the following command with the `--type` argument:

```cmd
.\tmdb-cli-tool --type <type>
```

Where `<type>` can be one of the following:
- `playing` — shows currently playing movies
- `popular` — shows popular movies
- `top` — shows shows popular movies
- `upcoming` — shows shows popular movies

Example:
```cmd
.\tmdb-cli-tool --type "top"
```

## Error Handling

The program will show an error message if: 
- The required argument `--type` is missing.
- An invalid movie type is provided.


## Security

**Important**: Never commit your API keys or tokens to a **public** repository. To keep them secure:
- Use environment variables to store sensitive information (e.g., `.env` file).
- Make sure to add the `.env` file to your `.gitignore` file to prevent accidental commits of sensitive data.

## Credits 
This project is inspired by the [roadmap.sh](https://roadmap.sh/) website, which provides a clear and structured guide for developers to follow in their learning journeys.
Visit [roadmap.sh](https://roadmap.sh/) to explore the world of programming with the help of interactive roadmaps and interesting projects for yourself! 
