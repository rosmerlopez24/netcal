#include <asio/error_code.hpp>
#include <asio/ip/network_v4.hpp>
#include <bitset>
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <string_view>
#include <tabulate.hpp>
#include <utility>

#define VERSION "v1.0.0"

using namespace asio;
using namespace asio::ip;
using namespace tabulate;

/* Simple parse from arguments cli */
auto parse_args(int argc, char *argv[]) -> std::optional<std::string_view>;

/* Displays the ipv4 network information table */
auto display_network_table(const network_v4 &network) -> void;

/* Convert number to binary in dotted format */
template <typename T> auto to_binary_and_format(const T &value) -> std::string;

int main(int argc, char *argv[]) {
  std::optional<std::string_view> argument{parse_args(argc, argv)};
  if (argument.has_value()) {
    error_code error;
    network_v4 network{make_network_v4(argument.value(), error)};
    if (error) {
      std::cout << "Error: " << error.message() << std::endl;
      std::exit(1);
    }
    display_network_table(network);
  }
  return 0;
}

auto parse_args(int argc, char *argv[]) -> std::optional<std::string_view> {
  int option{0};
  while ((option = getopt(argc, argv, "va:")) != -1) {
    if (std::cmp_equal(option, static_cast<int>('v'))) {
      std::cout << VERSION << std::endl;
      std::exit(1);
    } else if (std::cmp_equal(option, static_cast<int>('a'))) {
      return std::optional<std::string_view>(optarg);
    }
  }
  return std::nullopt;
}

auto display_network_table(const network_v4 &network) -> void {
  Table data{};

  /* Set data to table */
  data.add_row({"Address", network.address().to_string(),
                to_binary_and_format(network.address().to_uint())});
  data.add_row({"Netmask", network.netmask().to_string(),
                to_binary_and_format(network.netmask().to_uint())});
  data.add_row({"Network", network.canonical().to_string(),
                to_binary_and_format(network.network().to_uint())});
  data.add_row({"Broadcast", network.broadcast().to_string(),
                to_binary_and_format(network.broadcast().to_uint())});
  data.add_row({"Start range", network.hosts().begin()->to_string(),
                to_binary_and_format(network.hosts().begin()->to_uint())});
  data.add_row({"End range", network.hosts().end()->to_string(),
                to_binary_and_format(network.hosts().end()->to_uint())});
  data.add_row({"Hosts", std::to_string(network.hosts().size())});

  /* Set format to table */
  data.column(0)
      .format()
      .font_align(FontAlign::center)
      .font_style({FontStyle::bold})
      .font_color(Color::blue);

  /* Displaying using overload operator */
  std::cout << data << std::endl;
}

template <typename T> auto to_binary_and_format(const T &value) -> std::string {
  /* Convert to binary */
  std::string container{};
  if (value > 0) {
    container = std::bitset<std::numeric_limits<T>::digits>(value).to_string();
  }

  /* Format to dotted */
  std::string result{};
  for (std::string::size_type index{0}; const auto &element : container) {
    result.push_back(element);
    if ((index + 1) % 8 == 0 && index != container.length() - 1) {
      result.push_back('.');
    }
    ++index;
  }
  return result;
}
