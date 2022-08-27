#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

class AdjacencyMatrix {
  int gVertices;
  int **gMatrix;
  bool gIsSymmetric;

  void load_adjacency_matrix_from_file(std::string file_name) {
    std::ifstream file(file_name);

    // Exit early if the file is not exist
    if (!file.good()) {
      std::cout << "Input file is not exist!" << std::endl;
      std::exit(1);
    }

    if (file.is_open()) {
      std::string line;
      for (int i = 0; std::getline(file, line); i++) {
        // Get the number of vertices in the first line
        if (i == 0) {
          int n = atoi(line.c_str());
          // Exit early if the number of vertices isn't met the requirement
          if (n <= 2) {
            std::cout << "Number of vertices should be greater than 2!"
                      << std::endl;
            exit(1);
          }
          gVertices = n;
          gMatrix = new int *[gVertices];
          continue;
        }

        int k = 0;
        int row_number = i - 1;

        gMatrix[row_number] = new int[gVertices];

        // Loop through the string characters
        // If the character != space -> convert to int then push to the array
        for (int j = 0; j < line.length(); j++) {
          if (line[j] != ' ') {
            gMatrix[row_number][k] = line[j] - '0';
            k++;
          }
        }
      }
      file.close();
    }
  }

  bool is_do_thi_vo_huong() {
    bool vo_huong = true;
    for (int i = 0; i < gVertices; i++) {
      for (int j = 0; j < gVertices; j++) {
        if (gMatrix[i][j] != gMatrix[j][i]) {
          vo_huong = false;
          break;
        }
      }
    }

    return vo_huong;
  }

  int count_canh_cua_do_thi() {
    int canh_do_thi = 0;

    for (int i = 0; i < gVertices; i++) {
      if (gIsSymmetric) {
        for (int j = 0 + i; j < gVertices; j++) {
          canh_do_thi += gMatrix[i][j];
        }
      } else {
        for (int j = 0; j < gVertices; j++) {
          if (gMatrix[i][j] > 0) {
            canh_do_thi += gMatrix[i][j];
          }
        }
      }
    }

    return canh_do_thi;
  }

  int count_so_cap_dinh_xuat_hien_canh_boi() {
    int count = 0;
    for (int i = 0; i < gVertices; i++) {
      if (gIsSymmetric) {
        for (int j = 0 + i; j < gVertices; j++) {
          if (gMatrix[i][j] > 1) {
            count++;
          }
        }
      } else {
        for (int j = 0; j < gVertices; j++) {
          if (gMatrix[i][j] > 1) {
            count++;
          }
        }
      }
    }

    return count;
  }

  int count_so_canh_khuyen() {
    int count = 0;
    for (int i = 0; i < gVertices; i++) {
      for (int j = 0; j < gVertices; j++) {
        if ((gMatrix[i][j] == 1) && (i == j)) {
          count++;
        }
      }
    }

    return count;
  }

  int **count_bac_directed() {
    int **counts = 0;
    counts = new int *[gVertices];

    for (int i = 0; i < gVertices; i++) {
      counts[i] = new int[2];

      for (int j = 0; j < gVertices; j++) {
        if (gMatrix[j][i] > 0) {
          counts[i][0] += gMatrix[j][i];
        }
        if (gMatrix[i][j] > 0) {
          counts[i][1] += gMatrix[i][j];
        }
      }
    }

    return counts;
  }

  std::vector<int> count_bac_undirected() {
    std::vector<int> degrees;

    for (int i = 0; i < gVertices; i++) {
      int count = 0;
      for (int j = 0; j < gVertices; j++) {
        if (gMatrix[i][j] != 0) {
          count += gMatrix[i][j];
        }
        if (i == j) {
          count += gMatrix[i][j];
        }
      }
      degrees.push_back(count);
    }

    return degrees;
  }

  int count_so_theo_dieu_kien(int so_dinh) {
    int count = 0;

    if (gIsSymmetric) {
      std::vector<int> degrees = count_bac_undirected();
      for (int i = 0; i < degrees.size(); i++) {
        if (degrees[i] == so_dinh) {
          count++;
          std::cout << "in" << std::endl;
        }
      }
    } else {
      int **degrees = count_bac_directed();
      for (int i = 0; (i < gVertices); i++) {
        if (degrees[i][0] + degrees[i][1] == so_dinh) {
          count++;
        }
      }
    }

    return count;
  }

  int count_so_dinh_treo() { return count_so_theo_dieu_kien(1); }
  int count_so_dinh_co_lap() { return count_so_theo_dieu_kien(0); }

public:
  AdjacencyMatrix(std::string file_name) {
    load_adjacency_matrix_from_file(file_name);
    gIsSymmetric = is_do_thi_vo_huong();
  }

  void print_number_of_vertices() { std::cout << gVertices << std::endl; }

  void print_adjacency_matrix_to_console() {
    for (int i = 0; i < gVertices; i++) {
      for (int j = 0; j < gVertices; j++) {
        std::cout << gMatrix[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  void print_ma_tran_ke() {
    gIsSymmetric ? std::cout << "Do thi vo huong" << std::endl
                 : std::cout << "Do thi co huong" << std::endl;
  }

  void print_so_canh_cua_do_thi() {
    std::cout << "So canh cua do thi: " << count_canh_cua_do_thi() << std::endl;
  }

  void print_so_cap_dinh_xuat_hien_canh_boi() {
    std::cout << "So cap dinh xuat hien canh boi: "
              << count_so_cap_dinh_xuat_hien_canh_boi() << std::endl;
  }

  void print_so_canh_khuyen() {
    std::cout << "So canh khuyen: " << count_so_canh_khuyen() << std::endl;
  }

  void xac_dinh_loai_do_thi() {
    bool co_canh_boi = count_so_cap_dinh_xuat_hien_canh_boi() > 0;
    bool co_khuyen = count_so_canh_khuyen() > 0;
    std::string loai_do_thi = "unknown";

    if (gIsSymmetric) {
      if (co_canh_boi) {
        // Co canh boi
        if (co_khuyen) {
          loai_do_thi = "Gia do thi";
        } else {
          loai_do_thi = "Da do thi";
        }
      } else {
        loai_do_thi = "Don do thi";
      }
    } else {
      if (co_khuyen) {
        if (co_canh_boi) {
          loai_do_thi = "Da do thi co huong";
        } else {
          loai_do_thi = "Do thi co huong";
        }
      }
    }
    std::cout << loai_do_thi << std::endl;
  }

  void print_degrees() {
    if (gIsSymmetric) {
      std::vector<int> degrees = count_bac_undirected();
      std::cout << "Bac cua tung dinh:" << std::endl;
      for (int i = 0; i < gVertices; i++) {
        std::cout << i << "(" << degrees[i] << ") ";
      }
      std::cout << std::endl;
    } else {
      int **degrees = count_bac_directed();
      std::cout << "Bac cua tung dinh:" << std::endl;
      for (int i = 0; i < gVertices; i++) {
        std::cout << i << "(" << degrees[i][0] << "-" << degrees[i][1] << ") ";
      }
      std::cout << std::endl;
    }
  }

  void print_so_dinh_treo() {
    std::cout << "So dinh treo: " << count_so_dinh_treo() << std::endl;
  }

  void print_so_dinh_co_lap() {
    std::cout << "So dinh co lap: " << count_so_dinh_co_lap() << std::endl;
  }
};

int main() {
  AdjacencyMatrix AM("input.txt");

  AM.print_number_of_vertices();
  AM.print_adjacency_matrix_to_console();
  AM.print_ma_tran_ke();
  AM.print_number_of_vertices();
  AM.print_so_canh_cua_do_thi();
  AM.print_so_cap_dinh_xuat_hien_canh_boi();
  AM.print_so_canh_khuyen();
  AM.print_so_dinh_treo();
  AM.print_so_dinh_co_lap();
  AM.print_degrees();
  AM.xac_dinh_loai_do_thi();

  std::cout << "-------------------------" << std::endl;

  AdjacencyMatrix AM2("input2.txt");

  AM2.print_number_of_vertices();
  AM2.print_adjacency_matrix_to_console();
  AM2.print_ma_tran_ke();
  AM2.print_number_of_vertices();
  AM2.print_so_canh_cua_do_thi();
  AM2.print_so_cap_dinh_xuat_hien_canh_boi();
  AM2.print_so_canh_khuyen();
  AM2.print_so_dinh_treo();
  AM2.print_so_dinh_co_lap();
  AM2.print_degrees();
  AM2.xac_dinh_loai_do_thi();

  return 0;
}
