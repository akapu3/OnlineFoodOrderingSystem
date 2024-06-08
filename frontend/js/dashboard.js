document.addEventListener('DOMContentLoaded', function() {
    fetch('http://localhost:8080/restaurants')
        .then(response => response.json())
        .then(data => {
            const restaurantsDiv = document.getElementById('restaurants');
            data.restaurants.forEach(restaurant => {
                const restaurantDiv = document.createElement('div');
                restaurantDiv.className = 'restaurant';
                restaurantDiv.innerHTML = `<h3>${restaurant.name}</h3><p>${restaurant.address}</p><button onclick="viewMenu(${restaurant.id})">View Menu</button>`;
                restaurantsDiv.appendChild(restaurantDiv);
            });
        });
});

function viewMenu(restaurantId) {
    fetch(`http://localhost:8080/menu/${restaurantId}`)
        .then(response => response.json())
        .then(data => {
            const menuDiv = document.getElementById('menu');
            menuDiv.innerHTML = ''; // Clear existing menu
            data.menu_items.forEach(item => {
                const itemDiv = document.createElement('div');
                itemDiv.className = 'menu-item';
                itemDiv.innerHTML = `<h4>${item.name}</h4><p>${item.description}</p><p>$${item.price.toFixed(2)}</p><button onclick="addToOrder(${item.id}, '${item.name}', ${item.price})">Add to Order</button>`;
                menuDiv.appendChild(itemDiv);
            });
        });
}

let order = [];

function addToOrder(menuItemId, name, price) {
    const item = order.find(i => i.menuItemId === menuItemId);
    if (item) {
        item.quantity += 1;
    } else {
        order.push({ menuItemId, name, price, quantity: 1 });
    }
    displayOrder();
}

function displayOrder() {
    const orderDiv = document.getElementById('order');
    orderDiv.innerHTML = '<h3>Your Order</h3>';
    order.forEach(item => {
        const itemDiv = document.createElement('div');
        itemDiv.innerHTML = `<p>${item.name} - ${item.quantity} x $${item.price.toFixed(2)}</p>`;
        orderDiv.appendChild(itemDiv);
    });

    const totalAmount = order.reduce((total, item) => total + item.price * item.quantity, 0);
    const totalDiv = document.createElement('div');
    totalDiv.innerHTML = `<p>Total: $${totalAmount.toFixed(2)}</p><button onclick="placeOrder()">Place Order</button>`;
    orderDiv.appendChild(totalDiv);
}

function placeOrder() {
    const userId = 1; // Assuming a logged-in user with ID 1
    const restaurantId = order.length > 0 ? order[0].restaurantId : null;

    fetch('http://localhost:8080/order', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            user_id: userId,
            restaurant_id: restaurantId,
            items: order.map(item => ({ menu_item_id: item.menuItemId, quantity: item.quantity }))
        })
    }).then(response => {
        if (response.status === 200) {
            alert('Order placed successfully!');
            order = [];
            displayOrder();
        } else {
            alert('Failed to place order.');
        }
    });
}
