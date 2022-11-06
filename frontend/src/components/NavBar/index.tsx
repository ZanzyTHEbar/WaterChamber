import { faBars } from "@fortawesome/free-solid-svg-icons";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import React from "react";
import { Link } from "react-router-dom";

export default function index() {
    return (
        <>
            <div className="navbar">
                <Link to="#" className="menubars">
                    <FontAwesomeIcon icon={faBars} />
                </Link>
            </div>
        </>
    );
}
