# Order Execution and Management System for Deribit Test

## Objective

This project aims to create an order execution and management system that allows users to trade on Deribit Test (https://test.deribit.com/). The system provides functionalities to place, cancel, and modify orders, as well as access order book data and view current positions.

## Getting Started

### Prerequisites

1. **Create a Deribit Test Account**
   - Visit [Deribit Test](https://test.deribit.com/) and sign up for a new account.

2. **Generate API Keys**
   - After creating your account, generate a set of API keys that will be used for authentication in your requests.

### Installation

1. **Clone the Repository:**

   Open a terminal and run:

   ```bash
   git clone https://github.com/yourusername/deribit-order-execution.git
   cd deribit-order-execution
   ```

2. **Open the Project in Xcode:**

   - Open Xcode and select `File > Open`.
   - Navigate to the cloned directory and open the `.xcodeproj` file.

3. **Install Dependencies:**

   This project uses cURL for HTTP requests. You may need to install it via Homebrew if you haven't already:

   ```bash
   brew install curl
   ```

### Configuration

- Update the configuration file (`config.json` or similar) with your API keys and any other required settings.

## Functionality

The system supports the following core functions:

- **Place Order**: Submit new orders to the market.
- **Cancel Order**: Cancel existing orders in the market.
- **Modify Order**: Change the parameters of existing orders.
- **Get Order Book**: Retrieve the current order book for specified trading pairs.
- **View Current Positions**: Check the status of current open positions.

### Supported Features

- Trading across **spot**, **futures**, and **options** markets.
- Access to **all supported symbols** on Deribit.

### Focus

The primary focus of this system is to provide full functionality for the above-mentioned functions while maintaining low latency in executing orders and retrieving data.

## Implementation Details

- The system utilizes **cURL** for making HTTP requests to the Deribit API. 
- The implementation aims to minimize standard artifacts to enhance performance and speed.
- C++11 or later is recommended for this project.

## Usage

1. **Build the Project:**
   - Click on the project name in the left sidebar, then select your target.
   - Choose `Product > Build` from the top menu or press `Cmd + B`.

2. **Run the Application:**
   - Click the play button in the top left corner of Xcode or select `Product > Run` from the menu.

3. **Follow the Prompts:**
   - The application will prompt you for input, or you can use the provided API to perform trading actions.

## Contributing

If you'd like to contribute to this project, please fork the repository and submit a pull request. For any issues or feature requests, please create an issue on GitHub.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Thanks to the Deribit team for providing an accessible testing platform.
- Special thanks to contributors and the open-source community for their continuous support.
```

### Notes:
- Replace `https://github.com/yourusername/deribit-order-execution.git` with the actual URL of your repository.
- Ensure you include any specific instructions or additional dependencies your project might have.
- You might want to add sections on "Testing," "Examples," or "Known Issues" depending on your project’s complexity.
