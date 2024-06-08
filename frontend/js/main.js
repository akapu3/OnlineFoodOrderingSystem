// main.js

// Common utility functions

/**
 * Perform a GET request to the specified URL and return the JSON response.
 * @param {string} url - The URL to fetch.
 * @returns {Promise<any>} - A promise that resolves with the JSON response.
 */
async function fetchJson(url) {
    const response = await fetch(url);
    if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status}`);
    }
    return await response.json();
}

/**
 * Perform a POST request to the specified URL with the given data and return the JSON response.
 * @param {string} url - The URL to fetch.
 * @param {object} data - The data to send in the POST request.
 * @returns {Promise<any>} - A promise that resolves with the JSON response.
 */
async function postJson(url, data) {
    const response = await fetch(url, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
    });
    if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status}`);
    }
    return await response.json();
}

/**
 * Display an alert message.
 * @param {string} message - The message to display.
 */
function showAlert(message) {
    alert(message);
}

/**
 * Redirect to a different page.
 * @param {string} url - The URL to redirect to.
 */
function redirectTo(url) {
    window.location.href = url;
}

// Event listeners for common actions
document.addEventListener('DOMContentLoaded', () => {
    const logoutButton = document.getElementById('logoutButton');
    if (logoutButton) {
        logoutButton.addEventListener('click', () => {
            // Clear user session or token here
            showAlert('Logged out successfully.');
            redirectTo('login.html');
        });
    }
});

// Export utility functions if needed
export { fetchJson, postJson, showAlert, redirectTo };
