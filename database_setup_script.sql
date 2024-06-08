CREATE DATABASE food_ordering_system;

USE food_ordering_system;

CREATE TABLE users (
                       id INT AUTO_INCREMENT PRIMARY KEY,
                       username VARCHAR(50) UNIQUE NOT NULL,
                       password VARCHAR(255) NOT NULL,
                       email VARCHAR(100) UNIQUE NOT NULL
);

CREATE TABLE restaurants (
                             id INT AUTO_INCREMENT PRIMARY KEY,
                             name VARCHAR(100) NOT NULL,
                             address VARCHAR(255) NOT NULL
);

CREATE TABLE menu_items (
                            id INT AUTO_INCREMENT PRIMARY KEY,
                            restaurant_id INT,
                            name VARCHAR(100),
                            description TEXT,
                            price DECIMAL(10, 2),
                            FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)
);

CREATE TABLE orders (
                        id INT AUTO_INCREMENT PRIMARY KEY,
                        user_id INT,
                        restaurant_id INT,
                        total_amount DECIMAL(10, 2),
                        status VARCHAR(50),
                        order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                        FOREIGN KEY (user_id) REFERENCES users(id),
                        FOREIGN KEY (restaurant_id) REFERENCES restaurants(id)
);

CREATE TABLE order_items (
                             id INT AUTO_INCREMENT PRIMARY KEY,
                             order_id INT,
                             menu_item_id INT,
                             quantity INT,
                             FOREIGN KEY (order_id) REFERENCES orders(id),
                             FOREIGN KEY (menu_item_id) REFERENCES menu_items(id)
);
