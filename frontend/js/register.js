document.getElementById('registerForm').addEventListener('submit', function(event) {
    event.preventDefault();
    const username = document.getElementById('reg_username').value;
    const password = document.getElementById('reg_password').value;
    const email = document.getElementById('reg_email').value;

    fetch('http://localhost:8080/register', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ username, password, email })
    }).then(response => {
        if (response.status === 200) {
            alert('Registration successful!');
            window.location.href = 'login.html';
        } else {
            alert('Registration failed.');
        }
    });
});
