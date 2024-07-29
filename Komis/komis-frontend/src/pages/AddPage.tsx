import React, { useState } from 'react';
import "../css/AddPage.css";
import ApiAdd from '../service/ApiAdd'
import axios from 'axios';

const AddPage = () => {
    const apiAdd = new ApiAdd();
    const [showCarForm, setShowCarForm] = useState(false);
    const [showEmployeeForm, setEmployeeForm] = useState(false);
    const [showEmployeeReplaceForm, setEmployeeReplaceForm] = useState(false);
    const [showManagerForm, setManagerForm] = useState(false);
    const [showChangeRoleForm, setChangeRoleForm] = useState(false);
    const [showEmployeeDeleteForm, setEmployeeDeleteForm] = useState(false);
    const [showUserDataForm, setUserDataForm] = useState(false);
    const [id, setId] = useState(-1);
    const [showCarDeleteForm, setCarDeleteForm] = useState(false);
    const [message, setMessage] = useState('');
    const [carDetails, setCarDetails] = useState({
        brand: '',
        model: '',
        price: 3000,
        showroomId: 1
    });
    const [employeeDetails, setEmployeeDetails] = useState({
        name: '',
        surname: '',
        role: '',
        login: '',
        email: '',
        password: ''
    });
    const user = JSON.parse(localStorage.getItem("user"));
    const [addedUser, setAddedUser] = useState(null);

    const handleInputChange = (data) => {
        const { name, value } = data.target;
        if (showCarForm)
            setCarDetails({
                ...carDetails,
                [name]: value
            });
        else
            setEmployeeDetails({
                ...employeeDetails,
                [name]: value
            });
    };

    const handleNewCar = () => {
        setUserDataForm(false);
        setShowCarForm(true);
        setEmployeeForm(false);
        setEmployeeDeleteForm(false);
        setManagerForm(false);
        setCarDeleteForm(false);
        setEmployeeReplaceForm(false);
        setChangeRoleForm(false);
        setMessage('');
        setEmployeeDetails({ name: '', surname: '', role: '', login: '', email: '', password: '' });
        setId(-1);
    };

    const handleCarSubmit = async (data) => {
        data.preventDefault();
        try {
            const newVehicle = await apiAdd.AddVehicle(carDetails);
            setCarDetails({ brand: '', model: '', price: 3000, showroomId: 1 });
            setMessage('New vehicle added!');
        } catch (error) {
            setMessage("Failed to add a new vehicle!");
        }
    };

    const handleNewEmployee = () => {
        setUserDataForm(false);
        setEmployeeForm(true);
        setEmployeeDeleteForm(false);
        setShowCarForm(false);
        setManagerForm(false);
        setCarDeleteForm(false);
        setEmployeeReplaceForm(false);
        setChangeRoleForm(false);
        setMessage('');
        setEmployeeDetails({ name: '', surname: '', role: '', login: '', email: '', password: '' });
        setId(-1);
    };

    const handleEmployeeSubmit = async (data) => {
        data.preventDefault();
        try {
            const newEmployee = await apiAdd.AddEmployee(employeeDetails);
            setEmployeeDetails({ name: '', surname: '', role: '', login: '', email: '', password: '' });
            setMessage('New employee added!');
        } catch (error) {
            setMessage("Failed to add a new employee!");
        }
    };

    const handleNewManager = () => {
        setUserDataForm(false);
        setEmployeeDeleteForm(false);
        setEmployeeForm(false);
        setShowCarForm(false);
        setCarDeleteForm(false);
        setManagerForm(true);
        setEmployeeReplaceForm(false);
        setChangeRoleForm(false);
        setMessage('');
        setEmployeeDetails({ name: '', surname: '', role: '', login: '', email: '', password: '' });
        setId(-1);
    };

    const handleManagerSubmit = async (data) => {
        data.preventDefault();
        try {
            const managerDetails = { ...employeeDetails, role: 'MANAGER' };
            const newEmployee = await apiAdd.AddEmployee(managerDetails);
            setEmployeeDetails({ name: '', surname: '', role: '', login: '', email: '', password: '' });
            setMessage('New manager added!');
        } catch (error) {
            setMessage("Failed to add a new manager!");
        }
    };

    const handleReplaceEmployee = () => {
        setUserDataForm(false);
        setEmployeeReplaceForm(true);
        setEmployeeForm(false);
        setEmployeeDeleteForm(false);
        setShowCarForm(false);
        setManagerForm(false);
        setCarDeleteForm(false);
        setChangeRoleForm(false);
        setMessage('');
        setEmployeeDetails({ name: '', surname: '', role: '', login: '', email: '', password: '' });
        setId(-1);
    };

    const handleEmployeeReplaceSubmit = async (data) => {
        data.preventDefault();
        try {
            const newEmployee = await apiAdd.ReplaceEmployee(id, employeeDetails);
            setEmployeeDetails({ name: '', surname: '', role: '', login: '', email: '', password: '' });
            setId(-1);
            setMessage('Employee replaced!');
        } catch (error) {
            setMessage("Failed to replaced the employee!");
        }
    };

    const handleChangeRole = () => {
        setUserDataForm(false);
        setChangeRoleForm(true);
        setEmployeeReplaceForm(false);
        setEmployeeForm(false);
        setEmployeeDeleteForm(false);
        setShowCarForm(false);
        setManagerForm(false);
        setCarDeleteForm(false);
        setMessage('');
        setEmployeeDetails({ name: '', surname: '', role: '', login: '', email: '', password: '' });
        setId(-1);
    };

    const handleChangeRoleSubmit = async (data) => {
        data.preventDefault();
        try {
            console.log("hello ",data);
            const changedRole = await apiAdd.ChangeRole(employeeDetails);
            setEmployeeDetails({ name: '', surname: '', role: '', login: '', email: '', password: '' });
            setId(-1);
            setMessage('Role changed!');
        } catch (error) {
            setMessage("Failed to change the role!");
        }
    };

    const handleDeleteEmployee = () => {
        setUserDataForm(false);
        setEmployeeDeleteForm(true);
        setEmployeeForm(false);
        setShowCarForm(false);
        setCarDeleteForm(false);
        setManagerForm(false);
        setEmployeeReplaceForm(false);
        setChangeRoleForm(false);
        setMessage('');
        setEmployeeDetails({ name: '', surname: '', role: '', login: '', email: '', password: '' });
        setId(-1);
    };

    const handleDeleteEmployeeSubmit = async (event) => {
        event.preventDefault();
        try {
            const deletedEmployee = await apiAdd.DeleteEmployee(id);
            setId(-1);
            setMessage('Employee deleted!');
        } catch (error) {
            setMessage('Failed to delete the employee!');
        }
    };

    const handleDeleteCar = () => {
        setUserDataForm(false);
        setCarDeleteForm(true);
        setEmployeeDeleteForm(false);
        setEmployeeForm(false);
        setShowCarForm(false);
        setManagerForm(false);
        setEmployeeReplaceForm(false);
        setChangeRoleForm(false);
        setMessage('');
        setEmployeeDetails({ name: '', surname: '', role: '', login: '', email: '', password: '' });
        setId(-1);
    };

    const handleDeleteCarSubmit = async (event) => {
        event.preventDefault();
        try {
            const deletedCar = await apiAdd.DeleteCar(id);
            setId(-1);
            setMessage('Car deleted!');
        } catch (error) {
            setMessage('Failed to delete the car!');
        }
    };

    const handleUserData = () => {
        setUserDataForm(true);
        setEmployeeDeleteForm(false);
        setEmployeeForm(false);
        setShowCarForm(false);
        setCarDeleteForm(false);
        setManagerForm(false);
        setEmployeeReplaceForm(false);
        setChangeRoleForm(false);
        setMessage('');
        setEmployeeDetails({ name: '', surname: '', role: '', login: '', email: '', password: '' });
        setId(-1);
    };

    const handleUserDataSubmit = async (data) => {
        data.preventDefault();
        try {
            const user = await apiAdd.GetUser(employeeDetails);
            setAddedUser(user);
            setEmployeeDetails({ name: '', surname: '', role: '', login: '', email: '', password: '' });
        } catch (error) {
            setMessage("Failed to get user data!");
        }
    };

    return (
        <div className="add-page">
            <div className="dropdown">
                <button className="dropbtn">Options &#9660;</button>
                {(
                    <div className="dropdown-content">
                        <a href="#" onClick={handleUserData}>Get user data</a>
                        <a href="#" onClick={handleNewCar}>New car</a>
                        <a href="#" onClick={handleNewEmployee}>New employee</a>
                        {user.role=="ADMIN" && (
                            <div>
                                <a href="#" onClick={handleNewManager}>New manager</a>
                            </div>
                        )}
                        <a href="#" onClick={handleReplaceEmployee}>Replace employee</a>
                        <a href="#" onClick={handleChangeRole}>Change role</a>
                        {user.role=="ADMIN" && (
                            <div>
                                <a href="#" onClick={handleDeleteCar}>Delete car</a>
                                <a href="#" onClick={handleDeleteEmployee}>Delete user</a>
                            </div>
                        )}
                    </div>
                )}
            </div>

            {showCarForm && (
                <div className="form-container">
                    <form className="car-form" onSubmit={handleCarSubmit}>
                        <label>
                            Brand:
                            <input 
                                type="text" 
                                name="brand" 
                                value={carDetails.brand} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Model:
                            <input 
                                type="text" 
                                name="model" 
                                value={carDetails.model} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Price:
                            <input 
                                type="number" 
                                name="price" 
                                value={carDetails.price} 
                                onChange={handleInputChange} 
                                step="500"
                                min="3000"
                                required 
                            />
                        </label>
                        <label>
                            Showroom id:
                            <input 
                                type="number" 
                                name="showroomId" 
                                value={carDetails.showroomId} 
                                onChange={handleInputChange} 
                                step="1"
                                min="1"
                                required
                            />
                        </label>
                        <button type="submit">Add new car</button>
                    </form>
                    {message && <p id="message">{message}</p>}
                </div>
            )}

            {showEmployeeForm && (
                <div className="form-container">
                    <form className="car-form" onSubmit={handleEmployeeSubmit}>
                        <label>
                            Name:
                            <input 
                                type="text" 
                                name="name" 
                                value={employeeDetails.name} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Surname:
                            <input 
                                type="text" 
                                name="surname" 
                                value={employeeDetails.surname} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Role:
                            <select 
                                name="role" 
                                value={employeeDetails.role} 
                                onChange={handleInputChange} 
                                className="role-select"
                                required
                            >
                                <option value="DEALER">Dealer</option>
                                <option value="REPAIRER">Repairer</option>
                            </select>
                        </label>
                         <label>
                            Login:
                            <input 
                                type="text" 
                                name="login" 
                                value={employeeDetails.login} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Email:
                            <input 
                                type="text" 
                                name="email" 
                                value={employeeDetails.email} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Password:
                            <input 
                                type="text" 
                                name="password" 
                                value={employeeDetails.password} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <button type="submit">Add new employee</button>
                    </form>
                    {message && <p id="message">{message}</p>}
                </div>
            )}

            {showManagerForm && (
                <div className="form-container">
                    <form className="car-form" onSubmit={handleManagerSubmit}>
                        <label>
                            Name:
                            <input 
                                type="text" 
                                name="name" 
                                value={employeeDetails.name} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Surname:
                            <input 
                                type="text" 
                                name="surname" 
                                value={employeeDetails.surname} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                         <label>
                            Login:
                            <input 
                                type="text" 
                                name="login" 
                                value={employeeDetails.login} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Email:
                            <input 
                                type="text" 
                                name="email" 
                                value={employeeDetails.email} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Password:
                            <input 
                                type="text" 
                                name="password" 
                                value={employeeDetails.password} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <button type="submit">Add new manager</button>
                    </form>
                    {message && <p id="message">{message}</p>}
                </div>
            )}

            {showEmployeeReplaceForm && (
                <div className="form-container">
                    <form className="car-form" onSubmit={handleEmployeeReplaceSubmit}>
                    <label>
                        Replaced employee id:
                        <input 
                            type="number" 
                            name="id" 
                            value={id}
                            onChange={(e) => {
                                const value = parseInt(e.target.value);
                                setId(value);
                            }} 
                            step="1"
                            required 
                        />
                    </label>
                        <label>
                            Name:
                            <input 
                                type="text" 
                                name="name" 
                                value={employeeDetails.name} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Surname:
                            <input 
                                type="text" 
                                name="surname" 
                                value={employeeDetails.surname} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Role:
                            <select 
                                name="role" 
                                value={employeeDetails.role} 
                                onChange={handleInputChange} 
                                className="role-select"
                                required
                            >
                                <option value="ROLE" >Choose role</option>
                                <option value="DEALER">Dealer</option>
                                <option value="REPAIRER">Repairer</option>
                            </select>
                        </label>
                         <label>
                            Login:
                            <input 
                                type="text" 
                                name="login" 
                                value={employeeDetails.login} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Email:
                            <input 
                                type="text" 
                                name="email" 
                                value={employeeDetails.email} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Password:
                            <input 
                                type="text" 
                                name="password" 
                                value={employeeDetails.password} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <button type="submit">Replace employee</button>
                    </form>
                    {message && <p id="message">{message}</p>}
                </div>
            )}

            {showChangeRoleForm && (
                <div className="form-container">
                    <form className="car-form" onSubmit={handleChangeRoleSubmit}>
                         <label>
                            Login:
                            <input 
                                type="text" 
                                name="login" 
                                value={employeeDetails.login} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <label>
                            Role:
                            <select 
                                name="role" 
                                value={employeeDetails.role} 
                                onChange={handleInputChange} 
                                className="role-select"
                                required
                            >
                                <option value="ROLE" >Choose role</option>
                                <option value="DEALER" >Dealer</option>
                                <option value="REPAIRER">Repairer</option>
                                <option value="MANAGER">Manager</option>
                            </select>
                        </label>
                        <button type="submit">Change role</button>
                    </form>
                    {message && <p id="message">{message}</p>}
                </div>
            )}

        {showEmployeeDeleteForm && (
            <div className="form-container">
                <form className="car-form" onSubmit={handleDeleteEmployeeSubmit}>
                    <label>
                        Employee id:
                        <input 
                            type="number" 
                            name="id" 
                            value={id}
                            onChange={(e) => {
                                const value = parseInt(e.target.value);
                                setId(value);
                            }} 
                            step="1"
                            required 
                        />
                    </label>
                    <button type="submit">Delete user</button>
                </form>
                {message && <p id="message">{message}</p>}
            </div>
        )}

        {showCarDeleteForm && (
            <div className="form-container">
                <form className="car-form" onSubmit={handleDeleteCarSubmit}>
                    <label>
                        Car id:
                        <input 
                            type="number" 
                            name="id" 
                            value={id}
                            onChange={(e) => {
                                const value = parseInt(e.target.value);
                                setId(value);
                            }} 
                            step="1"
                            required 
                        />
                    </label>
                    <button type="submit">Delete car</button>
                </form>
                {message && <p id="message">{message}</p>}
            </div>
        )}

            {showUserDataForm && (
                <div className="form-container">
                    <form className="car-form" onSubmit={handleUserDataSubmit}>
                         <label>
                            Login:
                            <input 
                                type="text" 
                                name="login" 
                                value={employeeDetails.login} 
                                onChange={handleInputChange} 
                                required 
                            />
                        </label>
                        <button type="submit">Get user data</button>
                    </form>
                    {addedUser && (
                        <div className="userD">
                            User data:
                            <p className="user">Name: {addedUser.name}</p>
                            <p className="user">Surname: {addedUser.surname}</p>
                            <p className="user">Role: {addedUser.role}</p>
                            <p className="user">Login: {addedUser.login}</p>
                            <p className="user">Email: {addedUser.email}</p>
                        </div>
                    )}
                    {message && <p id="message">{message}</p>}
                </div>
            )}
        </div>
    );
};

export default AddPage;
