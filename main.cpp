/********************************************************************************
 *Stok Takip Uygulamasý
 *
 * Bu program, bir stok takip uygulamasýdýr. Kullanýcýlar ürün ekleyebilir,
 * silebilir, güncelleyebilir, mevcut ürünleri görüntüleyebilir ve
 * toplam stok deðerini hesaplayabilirler.
 ********************************************************************************/

#include <iostream>
#include <string>
#include <vector>

#define CLEAR std::cout << "\x1b[2J\x1b[1;1H"
/**************************************************************
*PRODUCT CLASS BURASI
**************************************************************/
class Product {
private:
	int _id;
	float _price;
	int _quantity;
	std::string _name;
	
public:
	int getId() {
		return _id;
	}
	void setId(int id) {
		_id = id;
	}
	std::string getName() {
		return _name;
	}
	void setName(std::string name) {
		_name = name;
	}
	int getQuantity() {
		return _quantity;
	}
	void setQuantity(int quantity) {
		_quantity = quantity;
	}
	float getPrice() {
		return _price;
	}
	void setPrice(float price) {
		_price = price;
	}

	void info() const {
		std::cout << "ID of the product: " << _id << std::endl;
		std::cout << "Name of the product: " << _name << std::endl;
		std::cout << "Quantity of the product: " << _quantity << std::endl;
		std::cout << "Price of the product: " << _price << std::endl;
		std::cout << "*******************************************" << std::endl;
	}
};

/**************************************************************
*DÝÐER FONKSÝYONLAR BURASI
**************************************************************/
void addProduct(std::vector<Product>& products) {
	Product newProduct;
	int productId;
	std::string productName;
	int productQuantity;
	float productPrice;

	std::cout << "Enter product ID: ";
	std::cin >> productId;
	auto it = std::find_if(products.begin(), products.end(), [productId](Product& p) { return p.getId() == productId; });
	if (it != products.end()) {
		std::cout << "Product with ID " << productId << " already exists. Cannot add the same ID." << std::endl;
		return;
	}
	newProduct.setId(productId);
	std::cout << "Enter product name: ";
	std::cin >> productName;
	newProduct.setName(productName);
	std::cout << "Enter product quantity: ";
	std::cin >> productQuantity;
	newProduct.setQuantity(productQuantity);
	std::cout << "Enter product price: ";
	std::cin >> productPrice;
	newProduct.setPrice(productPrice);
	products.push_back(newProduct);
	CLEAR;
	std::cout << "Product added successfully.\n";
}

void displayProducts(const std::vector<Product>& products) {
	for (const auto& product : products) {
		product.info();
	}
}

void deleteProductById(std::vector<Product>& products, int id) {
	auto it = products.begin();
	while (it != products.end()) {
		if (it->getId() == id) {
			it = products.erase(it);
			std::cout << "Product with ID " << id << " deleted successfully." << std::endl;
			return;
		} else { ++it; }
	}

	std::cout << "Product with ID " << id << " not found." << std::endl;
}

void updateProduct(std::vector<Product>& products, int id) {
	for (auto& product : products) {
		if (product.getId() == id) {
			std::string newName;
			std::cout << "Enter new product name: ";
			std::cin >> newName;
			product.setName(newName);

			int newQuantity;
			std::cout << "Enter new product quantity: ";
			std::cin >> newQuantity;
			product.setQuantity(newQuantity);

			float newPrice;
			std::cout << "Enter new product price: ";
			std::cin >> newPrice;
			product.setPrice(newPrice);

			std::cout << "Product with ID " << id << " updated successfully." << std::endl;
			return;
		}
	}

	std::cout << "Product with ID " << id << " not found." << std::endl;
}

float calculateTotalStockValue(std::vector<Product>& products) {
	float totalValue = 0.0;

	for (Product& product : products) {
		totalValue += product.getPrice() * product.getQuantity();
	}

	return totalValue;
}

/**************************************************************
*ANA FONKSÝYON BURASI
**************************************************************/
int main() {
	std::vector<Product> products;
	int choice;
	do {
		std::cout << "1. Add Product\n2. Delete Product\n3. Update Product\n4. View Products\n5. Calculate Total Stock Value\n0. Exit\n";
		std::cin >> choice;
		switch (choice) {
			case 1: CLEAR; 
				addProduct(products); break;
			case 2: CLEAR; 
				int deleteId; 
				std::cout << "Enter the ID of the product to delete: ";
				std::cin >> deleteId; 
				deleteProductById(products, deleteId); break;
			case 3: CLEAR;
				int updateId;
				std::cout << "Enter the ID of the product to update: ";
				std::cin >> updateId;
				updateProduct(products, updateId); break;
			case 4: CLEAR; 
				displayProducts(products); break;
			case 5: CLEAR;
				std::cout << "Total Stock Value: " << calculateTotalStockValue(products) << "TL" << std::endl;
				break;
		}
		
	} while (choice != 0);

	return 0;
}