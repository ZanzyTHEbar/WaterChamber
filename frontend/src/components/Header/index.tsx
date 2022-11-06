import logo from "/images/logo.png";
import { faGear } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { Link } from "react-router-dom";

export default function Header(props) {
    return (
        <header
            className="container px-4 py-2 flex items-center justify-between mx-auto"
            style={{
                paddingTop: "20px",
            }}
        >
            <div className="navbar">
                <Link to="#" className="menubars">
                    <button className="ml-4 p-1 hover:bg-gray-200 border rounded-full py-3 px-4 mr-5 shadow-md hover:shadow-xl focus:bg-gray-100 transition duration-200 ease-in focus:shadow-inner">
                        <FontAwesomeIcon icon={faGear} />
                    </button>
                </Link>
            </div>
            <h1 className="ml-4 text-xl text-gray-500 fond-bold">
                <span className="text-gray-900">{props.name}</span> Data
            </h1>
            <h2 className="ml-4 text-xl text-gray-500 font-bold">
                <span className="text-gray-900">ESP32</span> Data Logger
            </h2>
            <img src={logo} alt="logo" className="ml-5 mr-0 w-15 h-12" />
        </header>
    );
}

/* 



export default function Header() {
    return (
        <header
            className="px-4 py-2 flex items-center"
            style={{
                paddingTop: "20px",
            }}
        >
            <img src={logo} alt="logo" className="mr-2 w-12 h-12" />
            <h1 className="mr-10 text-xl text-gray-500 fond-bold">
                <span className="text-gray-900">Water Chamber</span> Data
            </h1>
            <button
                onClick={handleReset}
                className="border rounded py-2 px-4 mr-5 shadow-md hover:shadow-xl focus:bg-gray-100 transition duration-200 ease-in focus:shadow-inner"
            >
                Reset
            </button>
            <button onClick={handlePrevMonth}>
                <span className="material-icons-outlined cursor-pointer text-gray-600 mx-2">
                    chevron_left
                </span>
            </button>
            <button onClick={handleNextMonth}>
                <span className="material-icons-outlined cursor-pointer text-gray-600 mx-2">
                    chevron_right
                </span>
            </button>
            <h2 className="ml-4 text-xl text-gray-500 font-bold">
                <span className="text-gray-900">ESP32</span> Data Logger
            </h2>
        </header>
    );
}

*/
