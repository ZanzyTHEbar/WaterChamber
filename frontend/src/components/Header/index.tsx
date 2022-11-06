import logo from "/images/logo.png";
import { faGear } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { Link } from "react-router-dom";
import Settings from "@pages/Settings";
import { useState } from "react";

export default function Header(props) {
    const [showSettings, setShowSettings] = useState(false);

    const toggleSettings = () => {
        setShowSettings(!showSettings);
    };

    return (
        <>
            <header
                className="container px-4 py-2 flex items-center justify-between mx-auto"
                style={{
                    paddingTop: "20px",
                }}
            >
                <div className="navbar">
                    <Link to="#" className="menubars">
                        <button
                            onClick={toggleSettings}
                            className="ml-4 p-1 hover:bg-gray-200 border rounded-full py-3 px-4 mr-5 shadow-md hover:shadow-xl focus:bg-gray-100 transition duration-200 ease-in focus:shadow-inner"
                        >
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
            <div
                className={
                    showSettings
                        ? "nav-menu active overflow-y-auto"
                        : "nav-menu overflow-y-auto"
                }
            >
                <Settings />
            </div>
        </>
    );
}
