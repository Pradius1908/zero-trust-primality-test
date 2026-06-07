import subprocess
import json

ENGINE = "./prime_engine"


def _run_command(args):
    """
    Runs the C++ executable and returns JSON.
    """

    try:
        result = subprocess.run(
            [ENGINE] + args,
            capture_output=True,
            text=True
        )

        if result.returncode != 0:
            return {
                "success": False,
                "error": result.stderr.strip()
            }

        return json.loads(result.stdout)

    except Exception as e:
        return {
            "success": False,
            "error": str(e)
        }


# ============================
# PRIME TESTING
# ============================

def prime_test(number):
    return _run_command(
        ["test", str(number)]
    )


# ============================
# RSA GENERATION
# ============================

def generate_rsa():
    return _run_command(
        ["rsa"]
    )


# ============================
# USER REGISTRATION
# ============================

def register_user(username):
    return _run_command(
        ["register", username]
    )


# ============================
# USER AUTHENTICATION
# ============================

def authenticate_user(username):
    return _run_command(
        ["auth", username]
    )


# ============================
# SYSTEM STATISTICS
# ============================

def get_stats():
    return _run_command(
        ["stats"]
    )


# ============================
# CARMICHAEL DEMO
# ============================

def run_carmichael_demo():

    result = subprocess.run(
        [ENGINE, "carmichael"],
        capture_output=True,
        text=True
    )

    return result.stdout


# ============================
# BENCHMARK
# ============================

def benchmark_number(number):

    result = subprocess.run(
        [ENGINE, "benchmark", str(number)],
        capture_output=True,
        text=True
    )

    return result.stdout
