# WebBrowser

A minimalist web browser implementation written in C++11 using Qt6, featuring a complete rendering pipeline from HTML parsing through layout calculation to pixel-perfect painting.

## Features

- **HTML Parsing**: Tokenizes and parses HTML documents
- **CSS Support**: Basic CSS parsing with tag and descendant selectors
- **Layout Engine**: Full layout calculation including block and line-based text layout
- **Network Stack**: HTTP/HTTPS support with TLS connections
- **Text Rendering**: Cached font handling and styled text drawing
- **GUI Framework**: Qt6-based multi-tab browsing interface

## Architecture

The browser is organized into modular components that handle distinct responsibilities:

### Core Components

- **Browser**: Main application window and tab management
  - `Browser.hpp/cpp` - Application initialization
  - `Tab.hpp/cpp` - Individual browser tab
  - `Canvas.hpp/cpp` - Rendering surface
  - `Chrome.hpp/cpp` - UI chrome and tab bar

- **HTML Parser** (`html/`)
  - `HTMLParser.hpp/cpp` - Tokenization and parsing
  - `Element.hpp` - DOM element representation
  - `Text.hpp` - Text node representation
  - `Token.hpp` - HTML token definitions

- **CSS Engine** (`css/`)
  - `CSSParser.hpp/cpp` - CSS rule parsing
  - `Style.hpp/cpp` - Style application and cascade
  - `Selector.hpp` - Selector base class
  - `TagSelector.hpp/cpp` - Element type selectors
  - `DescendantSelector.hpp/cpp` - Descendant combinators

- **Layout Engine** (`layout/`)
  - `Layout.hpp` - Base layout class
  - `DocumentLayout.hpp/cpp` - Root document layout
  - `BlockLayout.hpp/cpp` - Block-level element layout
  - `LineLayout.hpp/cpp` - Inline text layout
  - `TextLayout.hpp/cpp` - Individual text fragment layout

- **Rendering** (`painting/`)
  - `DrawCmd.hpp` - Drawing command base
  - `DrawText.hpp/cpp` - Text drawing
  - `DrawRect.hpp/cpp` - Rectangle drawing

- **Network Stack** (`network/`)
  - `URL.hpp/cpp` - URL parsing and HTTP requests
  - `Connection.hpp` - Connection base class
  - `TcpConnection.hpp/cpp` - TCP connections
  - `TlsConnection.hpp/cpp` - TLS/SSL connections

- **Utilities** (`util/`)
  - `Util.hpp/cpp` - General utilities
  - `CachedFont.hpp/cpp` - Font caching for performance

## Data Flow

The browser processes web content through the following pipeline:

```
URL Request → HTTP/TLS Connection → HTML Parsing → DOM Tree
                                                         ↓
                                                   CSS Parsing & Style
                                                         ↓
                                                   Layout Calculation
                                                         ↓
                                                   Render/Paint to Canvas
                                                         ↓
                                                   Display in Window
```

## Requirements

- **CMake**: 3.16 or later
- **C++11** compatible compiler
- **Qt6**: Core and Widgets modules
- **OpenSSL**: For HTTPS support

## Usage

Launch the browser with a URL:

```bash
./webbrowser http://example.com
```

Or for HTTPS:

```bash
./webbrowser https://example.com
```

The browser will:
1. Request the webpage via HTTP/HTTPS
2. Parse the HTML
3. Apply CSS styles
4. Calculate layout
5. Render and display the result

## Project Structure

```
webbrowser/
├── CMakeLists.txt          # Build configuration
├── include/                # Public headers
│   ├── browser/            # Browser UI components
│   ├── css/                # CSS engine
│   ├── html/               # HTML parser
│   ├── layout/             # Layout engine
│   ├── network/            # Network stack
│   ├── painting/           # Rendering
│   └── util/               # Utilities
├── src/                    # Implementation files
│   ├── main.cpp           # Entry point
│   ├── browser/           # Browser implementations
│   ├── css/               # CSS implementations
│   ├── html/              # HTML parser implementations
│   ├── layout/            # Layout implementations
│   ├── network/           # Network implementations
│   ├── painting/          # Rendering implementations
│   └── util/              # Utility implementations
├── resources/             # Static resources (CSS, etc.)
└── build/                 # Build artifacts (generated)
```

## Design Highlights

- **Modular Architecture**: Each component handles one responsibility
- **Header-only Interfaces**: Clean separation between interface and implementation
- **Efficient Rendering**: Cached fonts reduce rendering overhead
- **Complete Stack**: End-to-end web rendering from network to pixels

## Limitations

This is a minimal web browser implementation for educational/demonstration purposes. It includes:
- Basic HTML and CSS support
- Simple layout algorithm
- No JavaScript support
- No image support
- No caching mechanisms

## Development Notes

- The browser startup path: `main → Browser → URL::request → HTMLParser::parse → DocumentLayout::layout`
- Layout calculations use a recursive tree traversal
- Styles cascade through selector specificity and element ancestry
